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
    auto start = container.begin();
    auto end = --container.end();
    for(auto i = start; i != end;++i)
    {
        std::cout<<*i<<".";
    }
    std::cout<<*end<<std::endl;
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

//нерекурсивная печать кортежа
//============================================================

template <typename T>
void foo(T arg)
{
    std::cout<<arg<<"\n";
}

template <typename T, typename... Args>
void foo(T arg,Args... args)
{
    std::cout<<arg<<".";
    foo(args...);
}



template<typename Tup, std::size_t... index>
void invoke_helper(Tup&& tup, std::index_sequence<index...>)
{
    foo(std::get<index>(tup)...);
}

template<typename Tup>
void invoke(Tup&& tup)
{
    constexpr auto Size = std::tuple_size<typename std::decay<Tup>::type>::value;
    invoke_helper(std::forward<Tup>(tup), std::make_index_sequence<Size>{});
}
//============================================================


/*!
 * Функция печати ip-адреса для кортежа
 * @tparam Args - типы в кортеже
 * @param t - объект кортежа
 */
template<typename... Args>
void print_ip(const std::tuple<Args...>& t)
{
    if(TupleChecker<decltype(t),sizeof...(Args)-1>::check_type(t))
        invoke(t);
    else
        std::cout<<"Types in tuple is not same";
    std::cout << "\n";
}
