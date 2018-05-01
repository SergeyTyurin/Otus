#pragma once

#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <condition_variable>

#include "bulkqueue.h"
#include "thread.h"
#include "printer.h"

class ThreadPool
{
    std::mutex m;
    std::condition_variable cv;
    std::vector<Thread> threads;
    BulkQueue qbulk;
    bool BulkEmpty;
    bool GetBulkEmpty();
public:
    ThreadPool(int count, std::string name);
    void Join();
    void Run(Writer* w);
    void OpenThreads();
    void Report();
    void CloseThreads();
    void EmplaceBulk(strVector);
    void ClearBulk();
    void SetTimestamp(const std::string&);

};

