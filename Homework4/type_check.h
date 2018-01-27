#pragma once

// Структура, которая проверяет, является ли тип контейнером
template <typename T>
struct is_container
{
private:
    template <typename C>
    static constexpr bool has_iterator(typename C::iterator*){ return true; };

    template <typename C>
    static constexpr bool has_iterator(...){ return false; };
public:
    static constexpr bool value = has_iterator<T>(nullptr);
};

// структура для проверки идентичности типов в кортеже
template<typename Tuple, std::size_t N>
struct TupleChecker {
    static bool check_type(const Tuple& t)
    {
        //рекурсивный вызов функции проверки
        if(std::is_same<decltype(std::get<0>(t)), decltype(std::get<N>(t))>::value)
            return true && TupleChecker<Tuple, N-1>::check_type(t);
        return false;
    }
};

template<typename Tuple>
struct TupleChecker<Tuple, 0> {
    static bool check_type(const Tuple& t)
    {
        return true;
    }
};