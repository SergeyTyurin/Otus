#pragma once

#include <iostream>
#include <type_traits>
#include <bitset>
#include <utility>
#include "type_check.h"

// Функция печати адреса для целочисленных типов
/*!
 * Функция печати ip-адреса для целочисленных типов
 * @tparam Integral - целочисленный тип
 * @param value - значение, передаваемое в функцию
 */
template <
        typename Integral,
        typename std::enable_if<
                std::is_integral<Integral>::value,
                Integral*
        >::type = nullptr
>
void print_ip(const Integral& value)
{
    std::bitset<8*sizeof(Integral)> bit(value);
    auto end = sizeof(Integral)-1;
    for(int i = 0; i < end; ++i)
    {
        std::cout<<std::bitset<8>(bit.to_string(),8*i,8).to_ulong()<<".";
    }
    std::cout<<std::bitset<8>(bit.to_string(), 8*end,8).to_ulong()<<std::endl;
}

/*!
 * Функция печати ip-адреса для целочисленных типов
 * @tparam Container - тип контейнера
 * @param container - объект контейнера
 */
template <
        typename Container,
        typename std::enable_if<
                is_container<Container>::value
                && !std::is_same<Container, std::string>::value,
                Container*
        >::type = nullptr
>
void print_ip(const Container& container)
{
    for(auto i = container.begin(); i != std::prev(container.end());++i)
    {
        std::cout<<*i<<".";
    }
    std::cout<<container.back()<<std::endl;
}

/*!
 * Функция печати ip-адреса для целочисленных типов
 * @tparam Container - тип контейнера
 * @param container - объект контейнера
 */
template <
        typename Container,
        typename std::enable_if<
                std::is_same<Container,std::string>::value,
                Container*
        >::type = nullptr
>
void print_ip(const Container& container)
{
    std::cout<<container<<std::endl;
}

// Структура печати элементов кортежа с рекурсивным обходом
template<typename Tuple, std::size_t N>
struct TuplePrinter {
    static void print(const Tuple& t)
    {
        TuplePrinter<Tuple, N-1>::print(t);
        std::cout << "." << std::get<N-1>(t);
    }
};

template<typename Tuple>
struct TuplePrinter<Tuple, 1> {
    static void print(const Tuple& t)
    {
        std::cout << std::get<0>(t);
    }
};

/*!
 * Функция печати ip-адреса для кортежа
 * @tparam Args - типы в кортеже
 * @param t - объект кортежа
 */
template<
        typename... Args,
        typename std::enable_if<SameTypeCheck<sizeof...(Args),Args...>::value,void*>::type = nullptr
>
void print_ip(const std::tuple<Args...>& t)
{
    TuplePrinter<decltype(t), sizeof...(Args)>::print(t);
    std::cout << "\n";
}

/*!
 * Функция печати ip-адреса для кортежа
 * @tparam Args - типы в кортеже
 * @param t - объект кортежа
 */
template<
        typename... Args,
        typename std::enable_if<!SameTypeCheck<sizeof...(Args),Args...>::value,void*>::type = nullptr
>
void print_ip(const std::tuple<Args...>& tp)
{
    std::cout<<"Types in tuple is not same\n";
}
