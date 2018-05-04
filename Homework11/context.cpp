#include "context.h"

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

void Context::Parse(const char* _data) {
    std::string command = _data;
    std::string word = "";
    for( auto it = command.begin(); it != command.end(); ++it )
    {
        if( *it == '\n' )
        {
            std::lock_guard<std::mutex> lk( m );
            this->data.emplace_back( word );
            word.clear();
            continue;
        }
        word += *it;
    }
    if( *std::prev( command.end() )!='\n' ) {
        std::lock_guard<std::mutex> lk( m );
        this->data.emplace_back(word);
    }
}

void Context::Receive(const char* _data, std::size_t size) {
    this->Parse(_data);
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

