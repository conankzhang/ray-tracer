#include "Dielectric.h"

#include "Math/Random.h"
#include "Trace/HitResult.h"

#include <cmath>

Dielectric::Dielectric(float refractionIndex)
    : m_RefractionIndex(refractionIndex)
{
}

bool Dielectric::ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const
{
    const float refractionRatio = hitResult.m_IsImpactOutside ? (1.0f / m_RefractionIndex) : m_RefractionIndex;
    const Float3 normalizedIncidentDirection = Float3::Normalized(incidentRay.Direction());

    const float cosTheta = std::fmin(Float3::Dot(-normalizedIncidentDirection, hitResult.m_ImpactNormal), 1.0f);
    const float sinTheta = std::sqrt(1.0f - cosTheta * cosTheta);

    Float3 scatterDirection;
    const bool cannotRefract = refractionRatio * sinTheta > 1.0f;
    if (cannotRefract)
    {
        scatterDirection = Float3::Reflect(normalizedIncidentDirection, hitResult.m_ImpactNormal);
    }
    else
    {
        scatterDirection = Float3::Refract(normalizedIncidentDirection, hitResult.m_ImpactNormal, refractionRatio);
    }

    scatteredRay = Ray(hitResult.m_ImpactLocation, scatterDirection);
    rayAttenuation = Float3(1.0f, 1.0f, 1.0f);

    return true;
}
