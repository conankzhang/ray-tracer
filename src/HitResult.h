#pragma once

#include "Double3.h"

struct HitResult final
{
    Double3 m_ImpactLocation;
    Double3 m_ImpactNormal;
    double rayEnd = 0.0;
};
