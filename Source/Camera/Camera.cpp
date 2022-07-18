#include "Camera.h"

Camera::Camera(const Float3& cameraOrigin, const Float3& focalPoint, const Float3& cameraUp, float verticalFov, float aspectRatio)
{
    const Float3 wVector = Float3::Normalized(cameraOrigin - focalPoint);
    const Float3 uVector = Float3::Normalized(Float3::Cross(cameraUp, wVector));
    const Float3 vVector = Float3::Cross(wVector, uVector);

    m_CameraOrigin = cameraOrigin;

    const float theta = Math::DegreesToRadians(verticalFov);
    const float height = std::tan(theta / 2.0f);
    const float viewportHeight = 2.0f * height;
    const float viewportWidth = viewportHeight * aspectRatio;

    m_HorizontalVector = viewportWidth * uVector;
    m_VerticalVector = viewportHeight * vVector;
    m_BottomLeft = m_CameraOrigin - m_HorizontalVector / 2.0f - m_VerticalVector / 2.0f - wVector;
}
