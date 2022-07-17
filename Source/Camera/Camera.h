#pragma once

#include "Math/Float3.h"
#include "Math/Ray.h"

class Camera
{
public:
    Camera(float aspectRatio);

    Ray GetRayForPixel(float u, float v) const;

private:
    Float3 m_CameraOrigin;

    Float3 m_HorizontalVector;
    Float3 m_VerticalVector;

    Float3 m_BottomLeft;
};

#include "Camera.inl"
