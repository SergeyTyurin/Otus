#pragma once

#include <vector>
#include <string>
#include <atomic>

class Writer
{
public:
    virtual void print(const std::string& bulk, const std::string& timestamp = "") = 0;
};

class ConsoleWriter:public Writer
{
public:
    void print(const std::string& bulk, const std::string& timestamp = "") override ;
};

class FileWriter:public Writer
{
public:
    void print(const std::string& bulk, const std::string& timestamp = "") override ;
};
