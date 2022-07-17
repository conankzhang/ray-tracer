#include "Sphere.h"

#include <cmath>

#include "Ray.h"
#include "Trace/HitResult.h"

bool Sphere::Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const
{
    const Float3 centerToOrigin = ray.Origin() - m_Center;

    // Quadratic Formula
    const float a = ray.Direction().LengthSquared();
    const float halfB = Float3::Dot(centerToOrigin, ray.Direction());
    const float c = centerToOrigin.LengthSquared() - m_Radius * m_Radius;

    const float discriminant = halfB * halfB - a * c;
    if (discriminant < 0.0f)
    {
        return false;
    }

    const float sqrtDiscriminant = std::sqrt(discriminant);

    // Get closest root that lies in range
    float root = (-halfB - sqrtDiscriminant) / a;
    if (root < rayStart || root > rayEnd)
    {
        root = (-halfB + sqrtDiscriminant) / a;
        if (root < rayStart || root > rayEnd)
        {
            return false;
        }
    }

    outResult.m_rayEnd = root;
    outResult.m_ImpactLocation = ray.At(outResult.m_rayEnd);
    const Float3 outsideNormal = (outResult.m_ImpactLocation - m_Center) / m_Radius;
    outResult.SetImpactNormal(outsideNormal, ray);

    return true;
}
