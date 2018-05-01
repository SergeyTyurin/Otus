#include "thread.h"
#include<iostream>
Thread::Thread(const std::string& n)
{
    name = n;
}

void Thread::Handler(Writer* w, BulkQueue& q, std::mutex& m, std::condition_variable& cv )
{
    while(!thread_closed)
    {
        std::unique_lock<std::mutex> lk(m);
        if(thread_closed)
        {
            lk.unlock();
            break;
        }
        cv.wait(lk, [this,&q]() { return !q.bulk.empty() || thread_closed;});
        if (q.bulk.empty())
        {
            lk.unlock();
            break;
        }
        else
        {
            strVector com = toVec(q.bulk.front());
            q.bulk.pop();
            lk.unlock();
            commands = (commands + static_cast<int>(com.size()));
            std::string complete_block = "bulk: ";
            for (auto it = com.begin(); it != std::prev(com.end()); ++it)
                complete_block += (*it + ", ");
            complete_block += *std::prev(com.end());
            blocks++;
            w->print(complete_block, q.timestamp+std::to_string(++unique_num));
        }
    }
}

void Thread::RunThread(Writer* w, BulkQueue& q, std::mutex& mx, std::condition_variable& cv)
{

    th = std::thread([this,w,&q, &mx, &cv](){this->Handler(w,q, mx, cv);});

};

void Thread::CloseThread()
{
    thread_closed = true;
}

int Thread::Blocks()
{
    return blocks;
};

int Thread::Commands()
{
    return commands;
};

std::string Thread::Name()
{
    return name;
};

void Thread::Join()
{
    th.join();
};
