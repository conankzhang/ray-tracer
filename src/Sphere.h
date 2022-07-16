#pragma once

#include "Traceable.h"

#include "Double3.h"

class Sphere final : public Traceable
{
public:
    Sphere(const Double3& center, double radius)
        : m_Center(center),
          m_Radius(radius)
    {
    }

    virtual bool Trace(const Ray& ray, double rayStart, double rayEnd, HitResult& outResult) const override;

private:
    Double3 m_Center;
    double m_Radius = 0.0;
};
