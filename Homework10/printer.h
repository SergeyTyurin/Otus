#pragma once
#include <vector>
#include <string>

class Writer
{
public:
    virtual void print(const std::string& bulk) = 0;
};

class ConsoleWriter:public Writer
{
public:
    void print(const std::string& bulk) override ;
};

class FileWriter:public Writer
{
public:
    void print(const std::string& bulk) override ;
    void setTimeStamp(std::string);
private:
    std::string timestamp;
    int unique_num = 0;
};
