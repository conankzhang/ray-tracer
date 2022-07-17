#pragma once

#include "Float3.h"

class Ray final
{
public:
    Ray()
    {
    }

    Ray(const Float3& origin, const Float3& direction)
        : m_Origin(origin),
          m_Direction(direction)
    {
    }

    const Float3& Origin() const;
    const Float3& Direction() const;
    Float3 At(float rayEnd) const;

private:
    Float3 m_Origin;
    Float3 m_Direction;
};

#include "Ray.inl"
