#pragma once

#include "Math/Float3.h"
#include "Math/Ray.h"

class Camera final
{
public:
    Camera(const Float3& cameraOrigin, const Float3& focalPoint, const Float3& cameraUp, float verticalFov, float aspectRatio);

    Ray GetRayForPixel(float u, float v) const;

private:
    Float3 m_CameraOrigin;

    Float3 m_HorizontalVector;
    Float3 m_VerticalVector;

    Float3 m_BottomLeft;
};

#include "Camera.inl"
