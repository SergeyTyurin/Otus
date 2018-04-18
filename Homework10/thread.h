#pragma once
#include <vector>
#include <string>
#include <queue>
#include <memory>
#include <condition_variable>
#include "printer.h"
#include <thread>

using strVector = std::vector<std::string>;

class Thread
{
public:
    Thread(const std::string& n);
    void Handler(Writer* w, std::queue<strVector>& q, std::mutex& m, std::condition_variable& cv );
    void RunThread(Writer* w, std::queue<strVector>& q, std::mutex& mx, std::condition_variable& cv);
    void CloseThread();
    int Blocks();
    int Commands();
    std::string Name();
    void Join();

private:
    strVector toVec(const strVector & s)
    {
        return s;
    }

    int commands=0;
    int blocks = 0;

    std::string name;
    std::thread th;
    bool thread_closed=false;

};

