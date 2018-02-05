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
template<size_t N, typename T, typename... Args>
struct SameTypeCheck {
    typedef T type;
    static constexpr bool value = std::is_same<T,typename SameTypeCheck<sizeof...(Args)-1,Args...>::type>::value
                                  && SameTypeCheck<sizeof...(Args)-1,Args...>::value;

};

template<typename T>
struct SameTypeCheck<0,T>
{
    typedef T type;
    static constexpr bool value = true;
};