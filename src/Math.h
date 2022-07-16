#pragma once

#include <limits>

namespace Math
{
    constexpr float s_Infinity = std::numeric_limits<float>::infinity();
    constexpr float s_Pi = 3.1415926535897932385f;

    float DegreesToRadians(float degrees);

} // namespace Math

#include "Math.inl"
