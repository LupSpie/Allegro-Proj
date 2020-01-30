#pragma once
#include <iostream>

template <typename T>
constexpr auto operator+(T e) noexcept
-> std::enable_if_t<std::is_enum<T>::value, std::underlying_type_t<T>>
{
    return static_cast<std::underlying_type_t<T>>(e);
}

enum class placeholder
{
    holder_1 = 1 << 0, // 000001
    holder_2 = 1 << 1, // 000010
    holder_3 = 1 << 2, // 000100
    holder_4 = 1 << 3, // 001000
    holder_5 = 1 << 4, // 010000
    holder_6 = 1 << 4  // 100000
};