#include "Metal.h"

#include "Math/Random.h"
#include "Trace/HitResult.h"

Metal::Metal(const Float3& albedo)
    : m_Albedo(albedo)
{
}

bool Metal::ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const
{
    const Float3 reflectedDirection = Float3::Reflect(Float3::Normalized(incidentRay.Direction()), hitResult.m_ImpactNormal);
    scatteredRay = Ray(hitResult.m_ImpactLocation, reflectedDirection);
    rayAttenuation = m_Albedo;

    return Float3::Dot(scatteredRay.Direction(), hitResult.m_ImpactNormal) > 0.0f;
}
