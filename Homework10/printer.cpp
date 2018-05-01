#include "printer.h"
#include <iostream>
#include <fstream>
#include <thread>
#include <sstream>

void ConsoleWriter::print(const std::string& bulk, const std::string& timestamp)
{
    std::cout<<bulk<<"\n";
}

void FileWriter::print(const std::string& bulk, const std::string& timestamp)
{
    auto id = std::this_thread::get_id();
    std::stringstream ss;
    ss <<id;
    std::string filename = "bulk"+timestamp+"_"+ss.str()+".log";
    std::ofstream out(filename);
    out<<bulk<<"\n";
}

