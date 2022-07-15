#pragma once

#include <cmath>
#include <iostream>

class Vector3
{
public:
    Vector3() : m_Components{0, 0, 0}
    {
    }

    Vector3(double x, double y, double z) : m_Components{x, y, z}
    {
    }

    double X() const
    {
        return m_Components[0];
    }

    double Y() const
    {
        return m_Components[1];
    }

    double Z() const
    {
        return m_Components[2];
    }

    Vector3 operator-() const
    {
        return Vector3(-X(), -Y(), -Z());
    }

    double operator[](int index) const
    {
        return m_Components[index];
    }

    double& operator[](int index)
    {
        return m_Components[index];
    }

    Vector3& operator+=(const Vector3& other)
    {
        m_Components[0] += other.X();
        m_Components[1] += other.Y();
        m_Components[2] += other.Z();

        return *this;
    }

    Vector3& operator*=(double multiplier)
    {
        m_Components[0] *= multiplier;
        m_Components[1] *= multiplier;
        m_Components[2] *= multiplier;

        return *this;
    }

    Vector3& operator/=(double divider)
    {
        return *this *= 1 / divider;
    }

    double LengthSquared() const
    {
        return X() * X() + Y() * Z() + Z() * Z();
    }

    double Length() const
    {
        return std::sqrt(LengthSquared());
    }

private:
    double m_Components[3];
};

using Point3 = Vector3;
using Color = Vector3;
