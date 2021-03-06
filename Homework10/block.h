#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <queue>
#include <memory>
#include <condition_variable>

#include "thread.h"
#include "threadpool.h"

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

    //BulkQueue bulk_file;
    //BulkQueue bulk_log;


    std::unique_ptr<ThreadPool> files;
    std::unique_ptr<ThreadPool> logs;

    int lines = 0;
    int commands_line = 0;
    int blocks = 0;
};
