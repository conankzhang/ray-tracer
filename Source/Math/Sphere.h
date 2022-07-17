#pragma once

#include "Trace/Traceable.h"

#include <memory>

#include "Float3.h"

class Material;

class Sphere final : public Traceable
{
public:
    Sphere(const Float3& center, float radius, const std::shared_ptr<Material> material)
        : m_Center(center),
          m_Radius(radius),
          m_Material(material)
    {
    }

    virtual bool Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const override;

private:
    Float3 m_Center;
    std::shared_ptr<Material> m_Material;
    float m_Radius = 0.0f;
};
