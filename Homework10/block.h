#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <thread>
#include <memory>
#include <condition_variable>
#include "printer.h"

using strVector = std::vector<std::string>;

class Thread
{
public:
    void SetName(std::string&& n)
    {
        name = n;
    };
    void Handler(Writer* w, std::condition_variable& cv,
                 std::mutex& m, std::queue<strVector>& q)
    {
        std::unique_lock<std::mutex> lk(m);
        cv.wait(lk);
        if(q.empty())
            lk.unlock();
        else {
            strVector com = toVec(q.front());
            commands = (commands+ static_cast<int>(com.size()))/count;
            std::string complete_block = "bulk: ";
            for(auto it = com.begin(); it!=std::prev(com.end());++it)
                complete_block += (*it + ", ");
            complete_block += *std::prev(com.end());
            q.pop();
            blocks++;
            lk.unlock();
            w->print(complete_block);
        }
    }
    void RunHandler(std::function<void (void)>&& f)
    {
        th = std::thread(f);
    };
    int Blocks()
    {
        return blocks;
    };
    int Commands()
    {
        return commands;
    };
    std::string Name()
    {
        return name;
    };
    void Join()
    {
        th.join();
    };
private:
    strVector toVec(const strVector & s)
    {
        return s;
    }

    int commands=0;
    int blocks = 0;
    std::string name;
    std::thread th;
    int count=1;
};

class Block
{
public:
    Block(int);
    ~Block();
    void writeCommands(std::string);
    void writeRestCommands();

private:
    void subblock(std::string);
    void flushCommands();

    size_t N;
    strVector commands;
    strVector sub_block;

    std::unique_ptr<Writer> consoleWriter;
    std::unique_ptr<Writer> fileWriter;

    std::queue<strVector> bulk_file;
    std::queue<strVector> bulk_log;

    std::condition_variable cv_f;
    std::mutex m_f;

    std::condition_variable cv_c;
    std::mutex m_c;

    Thread log;
    Thread file1;
    Thread file2;
    int lines = 0;
    int commands_line = 0;
    int blocks = 0;

    int done=0;
};
