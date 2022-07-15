#pragma once

#include <cmath>

class Vector3
{
public:
    Vector3()
        : m_Components{0, 0, 0}
    {
    }

    Vector3(double x, double y, double z)
        : m_Components{x, y, z}
    {
    }

    double X() const;
    double Y() const;
    double Z() const;

    Vector3 operator-() const;

    double operator[](int index) const;
    double& operator[](int index);

    Vector3& operator+=(const Vector3& other);
    Vector3& operator*=(double multiplier);
    Vector3& operator/=(double divisor);

    double LengthSquared() const;
    double Length() const;

    static double Dot(const Vector3& left, const Vector3& right);
    static Vector3 Cross(const Vector3& left, const Vector3& right);
    static Vector3 Normalized(const Vector3& vector);

private:
    double m_Components[3];
};

#include "Vector3.inl"
