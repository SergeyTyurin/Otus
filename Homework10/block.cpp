#include <iostream>
#include <ctime>
#include "block.h"

Block::Block(int size)
{
    N = size;
    consoleWriter.reset(new ConsoleWriter());
    fileWriter.reset(new FileWriter());
    log.SetName("log");
    file1.SetName("file1");
    file2.SetName("file2");

    log.RunHandler([this]() {
        while(!done)
            log.Handler(consoleWriter.get(),this->cv_c,this->m_c,bulk_log);
    });

    file1.RunHandler([this]() {
        while(!done)
            file1.Handler(fileWriter.get(),this->cv_c,this->m_c,bulk_file);
    });

    file2.RunHandler([this]() {
        while(!done)
            file2.Handler(fileWriter.get(),this->cv_c,this->m_c,bulk_file);
    });
}
Block::~Block()
{
    cv_c.notify_all();
    cv_f.notify_all();

    log.Join();
    file1.Join();
    file2.Join();

    std::cout<<"main thread - "<<lines<<" lines, "<<commands_line<<" commands, "<<blocks<<" blocks\n";
    std::cout<<log.Name()<<" thread - "<<log.Blocks()<<" blocks, "<<log.Commands()<<" commands\n";
    std::cout<<file1.Name()<<" thread - "<<file1.Blocks()<<" blocks, "<<file1.Commands()<<" commands\n";
    std::cout<<file2.Name()<<" thread - "<<file2.Blocks()<<" blocks, "<<file2.Commands()<<" commands\n";

}

void Block::writeCommands(std::string com)
{
    lines++;
    if (com != "{" && com != "}") {
        if (commands.empty())
            dynamic_cast<FileWriter *>(fileWriter)->setTimeStamp(std::to_string(std::time(nullptr)));
        commands.push_back(com);
        commands_line++;
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
    if(sub_block.empty() && !commands.empty())
    {
        blocks++;
        bulk_file.emplace(commands);
        this->cv_f.notify_all();
        bulk_log.emplace(commands);
        this->cv_c.notify_all();
        commands.clear();
    }
}

void Block::writeRestCommands()
{
    done = 1;
    flushCommands();
}
