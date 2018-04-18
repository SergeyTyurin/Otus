#include "printer.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>

void ConsoleWriter::print(const std::string& bulk)
{
    std::cout<<bulk<<"\n";
}

void FileWriter::print(const std::string& bulk)
{
    auto id = std::this_thread::get_id();
    std::stringstream ss;
    ss <<++unique_num; //unique part in filename (thread_id + ++int)
    std::string filename = "bulk"+timestamp+"_"+ss.str()+".log";
    std::ofstream out(filename);
    out<<bulk<<"\n";
}


void FileWriter::setTimeStamp(std::string str)
{
    timestamp = str;
}

