#pragma once

inline float Math::DegreesToRadians(float degrees)
{
    return degrees * s_Pi / 180.0f;
}

inline float Math::Clamp(float value, float min, float max)
{
    if (value < min)
    {
        return min;
    }
    else if (value > max)
    {
        return max;
    }

    return value;
}
