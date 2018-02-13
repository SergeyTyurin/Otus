#pragma once

#include "convert.h"
#include "internlayers.h"

template<typename Type, Type _default, int dimension=2, int current_level=2>
class Matrix
{
private:
    std::array<int,dimension> coordinates;
    static constexpr int next_dimension = dimension-1 > 0 ? dimension-1 : 1;
    NextLevel<Type, _default, dimension, next_dimension> *next_level = nullptr;

public:
    class iterator {
    public:
        iterator(typename std::map<std::array<int,dimension>,Type>::iterator _iter):iter(_iter)
        {
        }

        iterator operator++()
        {
            iter = std::next(iter);
            return *this;
        }

        typename generate_tuple_type<int,dimension,Type>::type operator*()
        {
            // создание нового кортежа путем конкатенации кортежа координат с кортежем значения
            return std::tuple_cat(array_to_tuple(iter->first),std::tuple<Type>(iter->second));
        }

        bool operator!=(const iterator &rhs) {
            return iter != rhs.iter;
        }
    private:
        typename std::map<std::array<int,dimension>,Type>::iterator iter;
    };

    Matrix()
    {
        next_level = new NextLevel<Type, _default, dimension, next_dimension>;
    }

    NextLevel<Type, _default, dimension, next_dimension>& operator[](int index)
    {
        coordinates[coordinates.size()-dimension]=index;
        next_level->SetCoordinates(coordinates);
        return *next_level;
    }

    size_t size()
    {
        return next_level->toEnd()->size();
    }

    iterator begin()
    {
        return iterator(next_level->toEnd()->Map().begin());
    }

    iterator end()
    {
        return iterator(next_level->toEnd()->Map().end());
    }
};


