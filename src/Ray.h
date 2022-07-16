#pragma once

#include "Double3.h"

class Ray final
{
public:
    Ray()
    {
    }

    Ray(const Double3& origin, const Double3& direction)
        : m_Origin(origin),
          m_Direction(direction)
    {
    }

    const Double3& Origin() const;
    const Double3& Direction() const;
    Double3 At(double rayEnd) const;

private:
    Double3 m_Origin;
    Double3 m_Direction;
};

#include "Ray.inl"
