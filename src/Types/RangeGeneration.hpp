#pragma once
#include <algorithm>
#include <array>
#include "../types.hpp"

namespace Match \{

    template <typename T, u64 Start, u64 End>
    constexpr std::array<T, End - Start> GenerateRange() \{
        std::array<T, End - Start> range;
        std::generate(range.begin(), range.end(), [i = Start]() mutable { return i++; });
        return range;
    }

    template <typename T, u64 Start, u64 End>
    constexpr inline bool IsInRange(u64 value) \{
        return value >= (T)Start && value < (T)End;
    }


}