#pragma once

#include <array>
#include <tuple>

// генерирование кортежа из массива

template<typename T, std::size_t N, std::size_t I = 0>
struct Converter
{
    template<typename... Elts>
    static auto cat(std::tuple<Elts...>&& t, const std::array<T, N>& a)
    -> decltype(Converter<T, N, I+1>::cat(std::tuple_cat(t, std::tuple<T>(a[I])), a))
    {
        return Converter<T, N, I+1>::cat(std::tuple_cat(t, std::tuple<T>(a[I])), a);
    }
};

template<typename T, std::size_t N>
struct Converter<T, N, N>
{
    template<typename... Elts>
    static std::tuple<Elts...> cat(std::tuple<Elts...>&& t, const std::array<T, N>& a)
    {
        return t;
    }
};

template<typename T, std::size_t N>
auto array_to_tuple(const std::array<T, N> a) -> decltype(Converter<T, N>::cat(std::tuple<>(), a))
{
    return Converter<T, N>::cat(std::tuple<>(), a);
}


// генерирование типа кортежа, например std::tuple<int,int>
template<typename T, unsigned N, typename... REST>
struct generate_tuple_type
{
    typedef typename generate_tuple_type<T, N-1, T, REST...>::type type;
};

template<typename T, typename... REST>
struct generate_tuple_type<T, 0, REST...>
{
    typedef std::tuple<REST...> type;
};
