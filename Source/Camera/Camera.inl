#pragma once

inline Ray Camera::GetRayForPixel(float u, float v) const
{
    return Ray(m_CameraOrigin, m_BottomLeft + u * m_HorizontalVector + v * m_VerticalVector - m_CameraOrigin);
}
