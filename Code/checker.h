#pragma once
#include <iostream>

template <typename T>
constexpr auto operator+(T e) noexcept 
-> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
{
    return static_cast<std::underlying_type_t<T>>(e);
}