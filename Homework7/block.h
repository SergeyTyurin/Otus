#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <memory>
#include "printer.h"

class Block
{
public:
    Block(int);

    void writeCommands(std::string);
    void writeRestCommands();

    std::vector<std::string> getArray();

private:
    void subblock(std::string);
    void flushCommands();
    size_t N;
    std::vector<std::string> commands;
    std::vector<std::string> sub_block;
    std::unique_ptr<Writer> consoleWriter;
    std::unique_ptr<Writer> fileWriter;
};
