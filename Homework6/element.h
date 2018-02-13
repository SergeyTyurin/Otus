#pragma once

#include <map>
#include <tuple>
#include <array>


// элемент матрицы , хранящий значения
template<typename Type, Type _default, int dimension>
class Element
{
private:
    std::array<int,dimension> coordinates;
    std::map<decltype(coordinates),Type> map;
public:
    Element<Type,_default,dimension>& operator=(const Type& value)
    {
        if(value!=_default)
            map[coordinates] = value;
        else
            map.erase(coordinates);
        return *this;
    }

    operator Type() {
        if(map.find(coordinates)!=map.end())
            return map[coordinates];
        return _default;
    }

    void SetCoordinates(const std::array<int,dimension>& c)
    {
        coordinates = c;
    }

    std::map<decltype(coordinates),Type>& GetMap()
    {
        return map;
    };

};
