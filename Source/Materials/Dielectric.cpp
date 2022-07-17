#include "Dielectric.h"

#include "Math/Random.h"
#include "Trace/HitResult.h"

Dielectric::Dielectric(float refractionIndex)
    : m_RefractionIndex(refractionIndex)
{
}

bool Dielectric::ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const
{
    const float refractionRatio = hitResult.m_IsImpactOutside ? (1.0f / m_RefractionIndex) : m_RefractionIndex;
    const Float3 normalizedIncidentDirection = Float3::Normalized(incidentRay.Direction());

    const Float3 refractionDirection = Float3::Refract(normalizedIncidentDirection, hitResult.m_ImpactNormal, refractionRatio);

    scatteredRay = Ray(hitResult.m_ImpactLocation, refractionDirection);
    rayAttenuation = Float3(1.0f, 1.0f, 1.0f);

    return true;
}
