#pragma once

inline Float3 operator+(const Float3& left, const Float3& right)
{
    return Float3(left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z());
}

inline Float3 operator-(const Float3& left, const Float3& right)
{
    return Float3(left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z());
}

inline Float3 operator*(const Float3& left, const Float3& right)
{
    return Float3(left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z());
}

inline Float3 operator*(const Float3& vector, float multiplier)
{
    return Float3(vector.X() * multiplier, vector.Y() * multiplier, vector.Z() * multiplier);
}

inline Float3 operator*(float multiplier, const Float3& vector)
{
    return vector * multiplier;
}

inline Float3 operator/(const Float3& vector, float divisor)
{
    return vector * (1 / divisor);
}

inline float Float3::X() const
{
    return m_Components[0];
}

inline float Float3::Y() const
{
    return m_Components[1];
}

inline float Float3::Z() const
{
    return m_Components[2];
}

inline float Float3::R() const
{
    return X();
}

inline float Float3::G() const
{
    return Y();
}

inline float Float3::B() const
{
    return Z();
}

inline Float3 Float3::operator-() const
{
    return Float3(-X(), -Y(), -Z());
}

inline float Float3::operator[](int index) const
{
    return m_Components[index];
}

inline float& Float3::operator[](int index)
{
    return m_Components[index];
}

inline Float3& Float3::operator+=(const Float3& other)
{
    m_Components[0] += other.X();
    m_Components[1] += other.Y();
    m_Components[2] += other.Z();

    return *this;
}

inline Float3& Float3::operator*=(float multiplier)
{
    m_Components[0] *= multiplier;
    m_Components[1] *= multiplier;
    m_Components[2] *= multiplier;

    return *this;
}

inline Float3& Float3::operator/=(float divisor)
{
    return *this *= 1 / divisor;
}

inline float Float3::LengthSquared() const
{
    return X() * X() + Y() * Y() + Z() * Z();
}

inline float Float3::Length() const
{
    return std::sqrt(LengthSquared());
}

inline float Float3::Dot(const Float3& left, const Float3& right)
{
    return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
}

inline Float3 Float3::Cross(const Float3& left, const Float3& right)
{
    return Float3(left.Y() * right.Z() - left.Z() * right.Y(),
                  left.Z() * right.X() - left.X() * right.Z(),
                  left.X() * right.Y() - left.Y() * right.X());
}

inline Float3 Float3::Normalized(const Float3& vector)
{
    return vector / vector.Length();
}

inline void Float3::PrintVector(std::ostream& ostream, const Float3& vector)
{
    ostream << "X: " << vector.X() << " Y: " << vector.Y() << " Z: " << vector.Z();
}

inline void Float3::WriteColor(std::ostream& ostream, const Float3& color)
{
    const int redInt = static_cast<int>(255.999 * color.R());
    const int greenInt = static_cast<int>(255.999 * color.G());
    const int blueInt = static_cast<int>(255.999 * color.B());

    ostream << redInt << ' ' << greenInt << ' ' << blueInt << '\n';
}
