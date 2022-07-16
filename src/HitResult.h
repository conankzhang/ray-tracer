#pragma once

#include "Double3.h"

struct HitResult final
{
    Double3 m_ImpactLocation;
    Double3 m_ImpactNormal;
    double m_rayEnd = 0.0;
};
