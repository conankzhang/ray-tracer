#include "Camera.h"

#include "Math/Random.h"

Camera::Camera(const Float3& cameraOrigin, const Float3& focalPoint, const Float3& cameraUp, float verticalFov, float aspectRatio, float aperture, float focusDistance)
{
    m_CameraBack = Float3::Normalized(cameraOrigin - focalPoint);
    m_CameraRight = Float3::Normalized(Float3::Cross(cameraUp, m_CameraBack));
    m_CameraUp = Float3::Cross(m_CameraBack, m_CameraRight);

    m_CameraOrigin = cameraOrigin;

    const float theta = Math::DegreesToRadians(verticalFov);
    const float height = std::tan(theta / 2.0f);
    const float viewportHeight = 2.0f * height;
    const float viewportWidth = viewportHeight * aspectRatio;

    m_HorizontalVector = focusDistance * viewportWidth * m_CameraRight;
    m_VerticalVector = focusDistance * viewportHeight * m_CameraUp;
    m_BottomLeft = m_CameraOrigin - m_HorizontalVector / 2.0f - m_VerticalVector / 2.0f - focusDistance * m_CameraBack;

    m_LensRadius = aperture / 2.0f;
}

Ray Camera::GetRayForPixel(float u, float v) const
{
    const Float3 randomVector = m_LensRadius * Math::RandomFloat3InUnitDisk();
    const Float3 offset = m_CameraRight * randomVector.X() + m_CameraUp * randomVector.Y();

    return Ray(m_CameraOrigin + offset, m_BottomLeft + u * m_HorizontalVector + v * m_VerticalVector - m_CameraOrigin - offset);
}
