#include <iostream>
#include <ctime>
#include "block.h"

Block::Block(int size)
{
    N = size;
    consoleWriter.reset(new ConsoleWriter());
    fileWriter.reset(new FileWriter());

    logs.reset(new ThreadPool(1,"log"));
    files.reset(new ThreadPool(2,"file"));

    logs->Run(consoleWriter.get());
    files->Run(fileWriter.get());
}
Block::~Block()
{
    logs->Join();
    files->Join();

    std::cout<<"main thread - "<<lines<<" lines, "<<commands_line<<" commands, "<<blocks<<" blocks\n";
    logs->Report();
    files->Report();

}

void Block::writeCommands(std::string com)
{
    ++lines;
    if (com != "{" && com != "}") {
        if (commands.empty())
        {
            files->SetTimestamp(std::to_string(std::time(nullptr)));
        }
        commands.push_back(com);
        ++commands_line;
        if (commands.size() == N)
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
    if(sub_block.empty())
    {
        if(!commands.empty()) {
            blocks++;

            logs->EmplaceBulk(commands);
            files->EmplaceBulk(commands);

            commands.clear();
        }

    }

    logs->OpenThreads();
    files->OpenThreads();
}

void Block::writeRestCommands()
{
    logs->ClearBulk();
    files->ClearBulk();

    {
        logs->CloseThreads();
        files->CloseThreads();
    }

}
