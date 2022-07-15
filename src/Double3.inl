#pragma once

inline Double3 operator+(const Double3& left, const Double3& right)
{
    return Double3(left.X() + right.X(), left.Y() + right.Y(), left.Z() + right.Z());
}

inline Double3 operator-(const Double3& left, const Double3& right)
{
    return Double3(left.X() - right.X(), left.Y() - right.Y(), left.Z() - right.Z());
}

inline Double3 operator*(const Double3& left, const Double3& right)
{
    return Double3(left.X() * right.X(), left.Y() * right.Y(), left.Z() * right.Z());
}

inline Double3 operator*(const Double3& vector, double multiplier)
{
    return Double3(vector.X() * multiplier, vector.Y() * multiplier, vector.Z() * multiplier);
}

inline Double3 operator*(double multiplier, const Double3& vector)
{
    return vector * multiplier;
}

inline Double3 operator/(const Double3& vector, double divisor)
{
    return vector * (1 / divisor);
}

double Double3::X() const
{
    return m_Components[0];
}

double Double3::Y() const
{
    return m_Components[1];
}

double Double3::Z() const
{
    return m_Components[2];
}

double Double3::R() const
{
    return X();
}

double Double3::G() const
{
    return Y();
}

double Double3::B() const
{
    return Z();
}

Double3 Double3::operator-() const
{
    return Double3(-X(), -Y(), -Z());
}

double Double3::operator[](int index) const
{
    return m_Components[index];
}

double& Double3::operator[](int index)
{
    return m_Components[index];
}

Double3& Double3::operator+=(const Double3& other)
{
    m_Components[0] += other.X();
    m_Components[1] += other.Y();
    m_Components[2] += other.Z();

    return *this;
}

Double3& Double3::operator*=(double multiplier)
{
    m_Components[0] *= multiplier;
    m_Components[1] *= multiplier;
    m_Components[2] *= multiplier;

    return *this;
}

Double3& Double3::operator/=(double divisor)
{
    return *this *= 1 / divisor;
}

double Double3::LengthSquared() const
{
    return X() * X() + Y() * Y() + Z() * Z();
}

double Double3::Length() const
{
    return std::sqrt(LengthSquared());
}

double Double3::Dot(const Double3& left, const Double3& right)
{
    return left.X() * right.X() + left.Y() * right.Y() + left.Z() * right.Z();
}

Double3 Double3::Cross(const Double3& left, const Double3& right)
{
    return Double3(left.Y() * right.Z() - left.Z() * right.Y(),
                   left.Z() * right.X() - left.X() * right.Z(),
                   left.X() * right.Y() - left.Y() * right.X());
}

Double3 Double3::Normalized(const Double3& vector)
{
    return vector / vector.Length();
}

void PrintVector(std::ostream& ostream, const Double3& vector)
{
    ostream << "X: " << vector.X() << " Y: " << vector.Y() << " Z: " << vector.Z();
}

void WriteColor(std::ostream& ostream, const Double3& color)
{
    const int redInt = static_cast<int>(255.999 * color.R());
    const int greenInt = static_cast<int>(255.999 * color.G());
    const int blueInt = static_cast<int>(255.999 * color.B());

    ostream << redInt << ' ' << greenInt << ' ' << blueInt << '\n';
}
