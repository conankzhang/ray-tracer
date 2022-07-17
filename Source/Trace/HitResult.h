#pragma once

#include <memory>

#include "Math/Float3.h"

class Material;
class Ray;

struct HitResult final
{
    void SetImpactNormal(const Float3& normal, const Ray& ray);

    Float3 m_ImpactLocation;
    Float3 m_ImpactNormal;

    std::shared_ptr<Material> m_Material;
    float m_rayEnd = 0.0f;
    bool m_IsImpactOutside = false;
};

#include "HitResult.inl"
