#pragma once

#include "Float3.h"

namespace Math
{
    static float RandomFloat();
    static float RandomFloat(float min, float max);

    static Float3 RandomFloat3();
    static Float3 RandomFloat3(float min, float max);
    static Float3 RandomFloat3InUnitSphere();
    static Float3 RandomUnitVector();

} // namespace Math

#include "Random.inl"
