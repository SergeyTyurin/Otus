#include "threadpool.h"
#include <iostream>
ThreadPool::ThreadPool(int count, std::string name)
{
    for(int i=0;i<count;++i)
    {
        std::string _name;
        if(count==1)
            _name = name;
        else
            _name = name + std::to_string(i + 1);

        threads.emplace_back(Thread(_name));
    }

}

void ThreadPool::Join()
{
    for(auto it= threads.begin();it!=threads.end();++it)
        (*it).Join();

}

void ThreadPool::Run(Writer* w)
{
    for(auto it= threads.begin();it!=threads.end();++it)
        (*it).RunThread(w, bulk, m, cv);
}

void ThreadPool::OpenThreads()
{
    cv.notify_one();
}

void ThreadPool::Report()
{
    for(auto i= threads.begin();i!=threads.end();++i)
        std::cout<<(*i).Name()<<" thread - "<<(*i).Blocks()<<" blocks, "<<(*i).Commands()<<" commands\n";
}

void ThreadPool::CloseThreads()
{
    std::unique_lock<std::mutex> lock(m);
    for(auto i= threads.begin();i!=threads.end();++i){
        (*i).CloseThread();
    }
    lock.unlock();
    cv.notify_all();
}

void ThreadPool::EmplaceBulk(strVector commands)
{
    std::unique_lock<std::mutex> lock(m);
    bulk.emplace(commands);
}

void ThreadPool::ClearBulk()
{
    while(!bulk.empty())
    {
        cv.notify_one();
    }
}