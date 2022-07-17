
#pragma once

#include "Material.h"

#include "Math/Float3.h"

class Dielectric final : public Material
{
public:
    Dielectric(float refractionIndex);

    virtual bool ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const override;

private:
    float m_RefractionIndex = 1.0f;
};
