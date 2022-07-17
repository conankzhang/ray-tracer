#pragma once

#include <random>

inline float Math::RandomFloat()
{
    static std::uniform_real_distribution<float> distribution(0.0f, 1.0f);
    static std::mt19937 generator;
    return distribution(generator);
}

inline float Math::RandomFloat(float min, float max)
{
    return min + (max - min) * RandomFloat();
}
