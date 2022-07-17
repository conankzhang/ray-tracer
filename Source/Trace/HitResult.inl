#pragma once

#include "Math/Ray.h"

inline void HitResult::SetImpactNormal(const Float3& outsideNormal, const Ray& ray)
{
    m_IsImpactOutside = Float3::Dot(ray.Direction(), outsideNormal) < 0.0f;
    m_ImpactNormal = m_IsImpactOutside ? outsideNormal : -outsideNormal;
}
