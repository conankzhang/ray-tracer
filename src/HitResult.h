#pragma once

#include "Float3.h"

struct HitResult final
{
    Float3 m_ImpactLocation;
    Float3 m_ImpactNormal;
    float m_rayEnd = 0.0;
};
