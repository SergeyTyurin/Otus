#pragma once

#include <vector>
#include <string>
#include <queue>
#include "thread.h"
#include <memory>
#include <condition_variable>
#include "printer.h"

class ThreadPool
{
    std::mutex m;
    std::condition_variable cv;
    std::vector<Thread> threads;
    std::queue<strVector> bulk;
public:
    ThreadPool(int count, std::string name);
    void Join();
    void Run(Writer* w);
    void OpenThreads();
    void Report();
    void CloseThreads();
    void EmplaceBulk(strVector);
    void ClearBulk();

};

