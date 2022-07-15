#pragma once

#include "Vector3.h"

class Ray
{
    Ray()
    {
    }

    Ray(const Vector3& origin, const Vector3& direction)
        : m_Origin(origin),
          m_Direction(direction)
    {
    }

    const Vector3& Origin() const;
    const Vector3& Direction() const;
    Vector3 At(double length) const;

private:
    Vector3 m_Origin;
    Vector3 m_Direction;
};

#include "Ray.inl"
