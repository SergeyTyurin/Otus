#include "block.h"
#include <iostream>
#include <ctime>



Block::Block(int size)
{
    N = size;
    consoleWriter.reset(new ConsoleWriter());
    fileWriter.reset(new FileWriter());

}

void Block::writeCommands(std::string com)
{
    if(com!="{" && com!="}")
    {
        if(commands.empty())
            dynamic_cast<FileWriter*>(fileWriter.get())->setTimeStamp(std::to_string(std::time(nullptr)));
        commands.push_back(com);
        if(commands.size()==N)
            flushCommands();
    }
    else
        subblock(com);
}


void Block::subblock(std::string com)
{
    if(com=="{")
    {
        flushCommands();
        sub_block.push_back(com);
        return;
    }

    if(com=="}")
    {
        sub_block.pop_back();
        flushCommands();
    }
}

void Block::flushCommands()
{
    if(sub_block.empty() && !commands.empty())
    {
        consoleWriter->setArray(commands);
        fileWriter->setArray(commands);

        consoleWriter->print();
        fileWriter->print();

        commands.clear();
    }
}

std::vector<std::string> Block::getArray()
{
    return commands;
}

void Block::writeRestCommands()
{
    flushCommands();
}

