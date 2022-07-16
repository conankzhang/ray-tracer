#pragma once

inline void HitResult::SetImpactNormal(const Float3& outsideNormal, const Ray& ray)
{
    m_ImpactIsOutside = Float3::Dot(ray.Direction(), outsideNormalnormal) < 0.0f;
    m_ImpactNormal = m_ImpactIsOutside ? outsideNormalnormal : -outsideNormalnormal;
}
