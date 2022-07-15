#pragma once

#include <iostream>

inline std::ostream& operator<<(std::ostream& ostream, const Vector3& vector)
{
    return ostream << "X: " << vector.X() << " Y: " << vector.Y() << " Z: " << vector.Z();
}

inline Vector3 operator+(const Vector3& left, const Vector3& right)
{
    return Vector3(left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z());
}

inline Vector3 operator-(const Vector3& left, const Vector3& right)
{
    return Vector3(left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z());
}

inline Vector3 operator*(const Vector3& left, const Vector3& right)
{
    return Vector3(left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z());
}

inline Vector3 operator*(const Vector3& vector, double multiplier)
{
    return Vector3(vector.X() * multiplier, vector.Y() * multiplier, vector.Z() * multiplier);
}

inline Vector3 operator*(double multiplier, const Vector3& vector)
{
    return vector * multiplier;
}

inline Vector3 operator/(const Vector3& vector, double divisor)
{
    return vector * (1 / divisor);
}

double Vector3::X() const
{
    return m_Components[0];
}

double Vector3::Y() const
{
    return m_Components[1];
}

double Vector3::Z() const
{
    return m_Components[2];
}

Vector3 Vector3::operator-() const
{
    return Vector3(-X(), -Y(), -Z());
}

double Vector3::operator[](int index) const
{
    return m_Components[index];
}

double& Vector3::operator[](int index)
{
    return m_Components[index];
}

Vector3& Vector3::operator+=(const Vector3& other)
{
    m_Components[0] += other.X();
    m_Components[1] += other.Y();
    m_Components[2] += other.Z();

    return *this;
}

Vector3& Vector3::operator*=(double multiplier)
{
    m_Components[0] *= multiplier;
    m_Components[1] *= multiplier;
    m_Components[2] *= multiplier;

    return *this;
}

Vector3& Vector3::operator/=(double divisor)
{
    return *this *= 1 / divisor;
}

double Vector3::LengthSquared() const
{
    return X() * X() + Y() * Y() + Z() * Z();
}

double Vector3::Length() const
{
    return std::sqrt(LengthSquared());
}

double Vector3::Dot(const Vector3& left, const Vector3& right)
{
    return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
}

Vector3 Vector3::Cross(const Vector3& left, const Vector3& right)
{
    return Vector3(left.Y() * right.Z() - left.Z() * right.Y(),
                   left.Z() * right.X() - left.X() * right.Z(),
                   left.X() * right.Y() - left.Y() * right.X());
}

Vector3 Vector3::Normalized(const Vector3& vector)
{
    return vector / vector.Length();
}
