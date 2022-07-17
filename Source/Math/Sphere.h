#pragma once

#include "Trace/Traceable.h"

#include "Float3.h"

class Sphere final : public Traceable
{
public:
    Sphere(const Float3& center, float radius)
        : m_Center(center),
          m_Radius(radius)
    {
    }

    virtual bool Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const override;

private:
    Float3 m_Center;
    float m_Radius = 0.0f;
};
