#pragma once
#include <iostream>
#include <string>

class GraphicElement
{
public:
    virtual void create() = 0;
    virtual void remove() = 0;
};

class Line:public GraphicElement
{
public:
    void create() override
    {
        std::cout<<"Create Line"<<std::endl;
    }

    void remove() override
    {
        std::cout<<"Remove Line"<<std::endl;
    }
};

class Square:public GraphicElement
{
public:
    void create() override
    {
        std::cout<<"Craete Square"<<std::endl;
    }

    void remove() override
    {
        std::cout<<"Remove Square"<<std::endl;
    }
};

class Triangle:public GraphicElement
{
public:
    void create() override
    {
        std::cout<<"Create Triangle"<<std::endl;
    }

    void remove() override
    {
        std::cout<<"Remove Triangle"<<std::endl;
    }
};

class Document
{
public:
    explicit Document()
    {
        std::cout<<"Create new document"<<std::endl;
    }

    explicit Document(const std::string& filename)
    {
        std::cout<<"Import document from file"<<filename<<std::endl;
    }

    void exportInFile(const std::string& filename)
    {
        std::cout<<"Export document in file"<<filename<<std::endl;
    }

    void createElement(GraphicElement* element)
    {
        element->create();
    }
    void removeElement(GraphicElement* element)
    {
        element->remove();
    }
};