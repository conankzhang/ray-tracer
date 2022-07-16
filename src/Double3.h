#pragma once

#include <cmath>
#include <iostream>

class Double3 final
{
public:
    Double3()
        : m_Components{0, 0, 0}
    {
    }

    Double3(double x, double y, double z)
        : m_Components{x, y, z}
    {
    }

    double X() const;
    double Y() const;
    double Z() const;

    double R() const;
    double G() const;
    double B() const;

    Double3 operator-() const;

    double operator[](int index) const;
    double& operator[](int index);

    Double3& operator+=(const Double3& other);
    Double3& operator*=(double multiplier);
    Double3& operator/=(double divisor);

    double LengthSquared() const;
    double Length() const;

    static double Dot(const Double3& left, const Double3& right);
    static Double3 Cross(const Double3& left, const Double3& right);
    static Double3 Normalized(const Double3& vector);

    static void PrintVector(std::ostream& ostream, const Double3& vector);
    static void WriteColor(std::ostream& ostream, const Double3& color);

private:
    double m_Components[3];
};

#include "Double3.inl"
