#pragma once
#include <vector>
#include <string>
#include <iostream>
#include "printer.h"

class Block
{
public:
    Block(int);

    void writeCommands(std::string);

    std::vector<std::string> getArray();

private:
    void subblock(std::string);
    void flushCommands();

    size_t N;
    std::vector<std::string> commands;
    std::vector<std::string> sub_block;
    Writer* consoleWriter = nullptr;
    Writer* fileWriter = nullptr;
};
