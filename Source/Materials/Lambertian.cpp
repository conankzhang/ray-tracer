#include "Lambertian.h"

#include "Math/Random.h"
#include "Trace/HitResult.h"

Lambertian::Lambertian(const Float3& albedo)
    : m_Albedo(albedo)
{
}

bool Lambertian::ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const
{
    Float3 scatterDirection = hitResult.m_ImpactNormal + Math::RandomFloat3InHemisphere(hitResult.m_ImpactNormal);

    if (Float3::IsNearZero(scatterDirection))
    {
        scatterDirection = hitResult.m_ImpactNormal;
    }

    scatteredRay = Ray(hitResult.m_ImpactLocation, scatterDirection);
    rayAttenuation = m_Albedo;

    return true;
}
