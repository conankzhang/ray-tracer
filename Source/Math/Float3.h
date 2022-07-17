#pragma once

#include <cmath>
#include <iostream>

class Float3 final
{
public:
    Float3()
        : m_Components{0.0f, 0.0f, 0.0f}
    {
    }

    Float3(float x, float y, float z)
        : m_Components{x, y, z}
    {
    }

    float X() const;
    float Y() const;
    float Z() const;

    float R() const;
    float G() const;
    float B() const;

    Float3 operator-() const;

    float operator[](int index) const;
    float& operator[](int index);

    Float3& operator+=(const Float3& other);
    Float3& operator*=(float multiplier);
    Float3& operator/=(float divisor);

    float LengthSquared() const;
    float Length() const;

    static float Dot(const Float3& left, const Float3& right);
    static Float3 Cross(const Float3& left, const Float3& right);
    static Float3 Normalized(const Float3& vector);
    static bool IsNearZero(const Float3& vector);

private:
    float m_Components[3];
};

#include "Float3.inl"
