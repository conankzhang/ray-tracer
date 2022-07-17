#pragma once

#include "Material.h"

#include "Math/Float3.h"

class Metal final : public Material
{
public:
    Metal(const Float3& albedo, float fuzziness);

    virtual bool ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const override;

private:
    Float3 m_Albedo;
    float m_Fuzziness = 1.0f;
};
