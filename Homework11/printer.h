#pragma once
#include <vector>
#include <string>

class Writer
{
public:
    virtual void print() = 0;
    virtual void setArray(std::vector<std::string>) = 0;
};

class ConsoleWriter:public Writer
{
public:
    void print() override ;
    void setArray(std::vector<std::string>) override ;
private:
    std::vector<std::string> v;
};

class FileWriter:public Writer
{
public:
    void print() override ;
    void setArray(std::vector<std::string>) override ;
    void setTimeStamp(std::string);
private:
    std::vector<std::string> v;
    std::string timestamp;
    int a=1;
};
