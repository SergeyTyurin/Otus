#include "context.h"
#include <algorithm>

Context::Context(std::size_t N)
{
    t = std::thread([this, N](){
        ptr.reset(new Block(static_cast<int>(N)));
        this->Handler();
    });
}

Context::~Context() {
    if(t.joinable()) {
        t.join();
    }
}

void Context::Handler(){
    while(!done)
    {
        std::unique_lock<std::mutex> lk(m);
        if(done)
        {
            ptr->writeRestCommands();
            lk.unlock();
            break;
        }
        cv.wait(lk/*, [this]() { return !data.empty() || done;}*/);

        if(data.empty())
        {
            ptr->writeRestCommands();
            lk.unlock();
            break;
        }

        if(!data.empty())
        {
            auto bulk = this->data.front();
            this->data.pop_front();
            ptr->writeCommands(bulk);
        }
        lk.unlock();
    }
}

void Context::Parse( const char* data, size_t len )
{
    std::string command;
    std::copy(data,data+len,std::back_inserter(command));
    std::string word;
    for(auto&& c:command)
    {
        if(!std::isspace(c) && !std::iscntrl(c)){
        //if(c!='\n' && c!='\0') {
            word += c;
            continue;
        }
        if(word.empty() && previous_word.empty())
        {
            this->data.emplace_back(word);
            continue;
        }
        if(!word.empty()) {
            this->data.emplace_back(word);
            word.clear();
        }
    }
    previous_word = word;
    if(!word.empty())
        this->data.emplace_back(word);

    std::lock_guard<std::mutex> lc( m );
    for(auto&& a : this->data)
        std::cout<<a<<" ";
    std::cout<<std::endl;
}

void Context::Receive(const char* _data, std::size_t size) {
    this->Parse(_data, size);
    cv.notify_one();
}

void Context::Disconnect() {
    HandleRest();
    done = true;
    cv.notify_one();
}

void Context::HandleRest()
{
    while( !QE )
    {
        cv.notify_one();
        QE = GetQE();
    }
}

bool Context::GetQE()
{
    std::lock_guard<std::mutex> lc( m );
    return this->data.empty();
}

