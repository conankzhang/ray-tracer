#pragma once

const Vector3& Ray::Origin() const
{
    return m_Origin;
}

const Vector3& Ray::Direction() const
{
    return m_Origin;
}

Vector3 Ray::At(double length) const
{
    return m_Origin + (m_Direction * length);
}
