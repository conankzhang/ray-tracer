#pragma once

#include "Ray.h"

inline void HitResult::SetImpactNormal(const Float3& outsideNormal, const Ray& ray)
{
    m_ImpactIsOutside = Float3::Dot(ray.Direction(), outsideNormal) < 0.0f;
    m_ImpactNormal = m_ImpactIsOutside ? outsideNormal : -outsideNormal;
}
