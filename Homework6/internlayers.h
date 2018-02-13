#pragma once

#include "element.h"

// промежуточные уровни матрицы

template<typename Type, Type _default, int dimension, int current_level>
class NextLevel
{
    std::array<int,dimension> coordinates;
    NextLevel<Type, _default, dimension, current_level-1>* next_level = nullptr;
public:
    NextLevel()
    {
        next_level = new NextLevel<Type, _default, dimension, current_level-1>;
    }

    void SetCoordinates(const std::array<int,dimension>& c)
    {
        coordinates = c;
    }

    NextLevel<Type, _default, dimension, current_level-1>& operator[](int index)
    { ;
        coordinates[coordinates.size()-current_level]=index;
        next_level->SetCoordinates(coordinates);
        return *next_level;
    };

    NextLevel<Type, _default, dimension, current_level-1>* toEnd()
    {
        return next_level->toEnd();
    };

};

// последний слой
template<typename Type, Type _default, int dimension>
class NextLevel<Type,_default,dimension,1>
{
private:
    std::array<int,dimension> coordinates;
    Element<Type,_default,dimension>* element = nullptr;
public:
    NextLevel()
    {
        element = new Element<Type,_default,dimension>;
    }

    Element<Type,_default,dimension>& operator[](int index)
    {
        coordinates[dimension-1]=index;
        element->SetCoordinates(coordinates);
        return *element;

    }

    void SetCoordinates(const std::array<int,dimension>& c)
    {
        coordinates = c;
    }

    size_t size()
    {
        return element->GetMap().size();
    }

    NextLevel<Type,_default,dimension,1>* toEnd()
    {
        return this;
    };

    std::map<decltype(coordinates), Type>& Map()
    {
        return element->GetMap();
    }
};