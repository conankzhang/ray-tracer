#include "Metal.h"

#include "Math/Random.h"
#include "Trace/HitResult.h"

Metal::Metal(const Float3& albedo, float fuzziness)
    : m_Albedo(albedo),
      m_Fuzziness(fuzziness < 1.0f ? fuzziness : 1.0f)

{
}

bool Metal::ScatterRay(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const
{
    const Float3 reflectedDirection = Float3::Reflect(Float3::Normalized(incidentRay.Direction()), hitResult.m_ImpactNormal);
    const Float3 fuzzyReflection = m_Fuzziness * Math::RandomFloat3InUnitSphere();
    scatteredRay = Ray(hitResult.m_ImpactLocation, reflectedDirection + fuzzyReflection);
    rayAttenuation = m_Albedo;

    const float dotResult = Float3::Dot(scatteredRay.Direction(), hitResult.m_ImpactNormal);
    return dotResult > 0.0f;
}
