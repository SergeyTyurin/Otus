#include "printer.h"
#include <iostream>
#include <fstream>
#include <sstream>
void ConsoleWriter::print()
{
    if(v.empty())
        return;
    std::cout<<"bulk: ";
    for(auto it = v.begin(); it!=std::prev(v.end());++it)
        std::cout<<*it<<", ";
    std::cout<<*std::prev(v.end())<<std::endl;
}

void ConsoleWriter::setArray(std::vector<std::string> arr)
{
    v=arr;
}


void FileWriter::print()
{
    std::stringstream ss;
    ss << a++;
    std::string filename = "bulk"+timestamp+ss.str()+".log";
    std::ofstream out(filename);
    if(v.empty())
        return;
    out<<"bulk: ";
    for(auto it = v.begin(); it!=std::prev(v.end());++it)
        out<<*it<<", ";
    out<<*std::prev(v.end())<<std::endl;
}

void FileWriter::setArray(std::vector<std::string> arr)
{
    v=arr;
}

void FileWriter::setTimeStamp(std::string str)
{
    timestamp = str;
}

