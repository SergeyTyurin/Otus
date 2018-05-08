#pragma once
#include <iostream>
#include <thread>
#include "block.h"
#include <mutex>
#include <condition_variable>
#include <deque>
class Context
{
public:
    Context(std::size_t);
    ~Context();
    void Handler();
    void Receive(const char* data, std::size_t size);
    void Parse( const char* data ,size_t);
    void Disconnect();
    void HandleRest();
    bool GetQE();
private:
    std::shared_ptr<Block> ptr;
    std::thread t;
    std::mutex m;
    std::condition_variable cv;
    bool done;
    std::deque<std::string> data;
    bool QE;
    std::string previous_word;
};