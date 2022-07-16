#pragma once

const Float3& Ray::Origin() const
{
    return m_Origin;
}

const Float3& Ray::Direction() const
{
    return m_Direction;
}

Float3 Ray::At(float rayEnd) const
{
    return m_Origin + (m_Direction * rayEnd);
}
