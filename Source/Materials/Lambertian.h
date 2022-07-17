#pragma once

#include "Material.h"

#include "Math/Float3.h"

class Lambertian final : public Material
{
public:
    Lambertian(const Float3& albedo);

    virtual bool Scatter(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const override;

private:
    Float3 m_Albedo;
};
