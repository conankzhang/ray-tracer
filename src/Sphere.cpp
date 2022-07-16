#include "Sphere.h"

#include <cmath>

#include "HitResult.h"
#include "Ray.h"

bool Sphere::Trace(const Ray& ray, double rayStart, double rayEnd, HitResult& outResult) const
{
    const Double3 centerToOrigin = ray.Origin() - m_Center;

    // Quadratic Formula
    const double a = ray.Direction().LengthSquared();
    const double halfB = Double3::Dot(centerToOrigin, ray.Direction());
    const double c = centerToOrigin.LengthSquared() - m_Radius * m_Radius;

    const double discriminant = halfB * halfB - a * c;
    if (discriminant < 0)
    {
        return false;
    }

    const double sqrtDiscriminant = std::sqrt(discriminant);

    // Get closest root that lies in range
    double root = (-halfB - sqrtDiscriminant) / a;
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
    outResult.m_ImpactNormal = (outResult.m_ImpactLocation - m_Center) / m_Radius;

    return true;
}
