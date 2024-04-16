#pragma once
#include <algorithm>
#include <array>
#include "../types.hpp"

namespace Match
{

    template<typename T, uSize Start, uSize End>
    constexpr std::array<T, End - Start> GenerateRange()
    {
        std::array<T, End - Start> range;
        std::generate(range.begin(), range.end(), [i = Start]() mutable { return i++; });
        return range;
    }

    template<typename T, uSize Start, uSize End>
    constexpr inline bool IsInRange(uSize value)
    {
        return value >= (T)Start && value < (T)End;
    }


}