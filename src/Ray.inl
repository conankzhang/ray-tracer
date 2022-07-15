#pragma once

const Double3& Ray::Origin() const
{
    return m_Origin;
}

const Double3& Ray::Direction() const
{
    return m_Direction;
}

Double3 Ray::At(double length) const
{
    return m_Origin + (m_Direction * length);
}
