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

inline Float3 Math::RandomFloat3()
{
    return Float3(RandomFloat(), RandomFloat(), RandomFloat());
}

inline Float3 Math::RandomFloat3(float min, float max)
{
    return Float3(RandomFloat(min, max), RandomFloat(min, max), RandomFloat(min, max));
}

inline Float3 Math::RandomFloat3InUnitSphere()
{
    while (true)
    {
        const Float3 randomFloat3 = RandomFloat3(-1.0f, 1.0f);
        if (randomFloat3.LengthSquared() >= 1.0f)
        {
            continue;
        }

        return randomFloat3;
    }
}

inline Float3 Math::RandomFloat3InHemisphere(const Float3& normal)
{
    const Float3 randomFloat3 = Math::RandomFloat3InUnitSphere();
    if (Float3::Dot(randomFloat3, normal) > 0.0f)
    {
        return randomFloat3;
    }
    else
    {
        return -randomFloat3;
    }
}

inline Float3 Math::RandomUnitVector()
{
    return Float3::Normalized(RandomFloat3InUnitSphere());
}
