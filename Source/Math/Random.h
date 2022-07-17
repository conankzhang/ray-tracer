#pragma once

#include "Float3.h"

namespace Math
{
    float RandomFloat();
    float RandomFloat(float min, float max);

    Float3 RandomFloat3();
    Float3 RandomFloat3(float min, float max);
    Float3 RandomFloat3InUnitSphere();

} // namespace Math

#include "Random.inl"
