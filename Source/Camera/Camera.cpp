#include "Camera.h"

Camera::Camera(float aspectRatio)
{
    constexpr float viewportHeight = 2.0f;
    const float viewportWidth = viewportHeight * aspectRatio;

    m_CameraOrigin = Float3(0.0f, 0.0f, 0.0f);

    m_HorizontalVector = Float3(viewportWidth, 0.0f, 0.0f);
    m_VerticalVector = Float3(0.0f, viewportHeight, 0.0f);

    constexpr float focalLength = 1.0f;
    const Float3 cameraLength(0.0f, 0.0f, focalLength);

    m_BottomLeft = m_CameraOrigin - m_HorizontalVector / 2.0f - m_VerticalVector / 2.0f - cameraLength;
}