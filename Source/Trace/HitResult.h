#pragma once

#include "Math/Float3.h"

class Ray;

struct HitResult final
{
    void SetImpactNormal(const Float3& normal, const Ray& ray);

    Float3 m_ImpactLocation;
    Float3 m_ImpactNormal;
    float m_rayEnd = 0.0f;
    bool m_ImpactIsOutside = false;
};

#include "HitResult.inl"
