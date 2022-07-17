#include <iostream>

#include "Float3.h"
#include "Float3.inl"
#include "HitResult.h"
#include "Math.h"
#include "Ray.h"
#include "Sphere.h"
#include "TraceableList.h"

Float3 getRayColorFromWorld(const Ray& ray, const TraceableList& world)
{
    HitResult result;

    if (world.Trace(ray, 0.0f, Math::s_Infinity, result))
    {
        return 0.5f * (result.m_ImpactNormal + Float3(1.0f, 1.0f, 1.0f));
    }

    // Lerp between colors for background
    const Float3 direction = Float3::Normalized(ray.Direction());
    const float rayEnd = 0.5f * (direction.Y() + 1.0f);
    return (1.0f - rayEnd) * Float3(1.0f, 1.0f, 1.0f) + (Float3(0.5f, 0.7f, 1.0f) * rayEnd);
}

int main()
{
    constexpr float aspectRatio = 16.0f / 9.0f;

    // Camera
    constexpr float viewportHeight = 2.0f;
    constexpr float viewportWidth = viewportHeight * aspectRatio;
    constexpr float focalLength = 1.0f;

    const Float3 cameraOrigin(0.0f, 0.0f, 0.0f);
    const Float3 cameraLength(0.0f, 0.0f, focalLength);

    const Float3 horizontalVector(viewportWidth, 0.0f, 0.0f);
    const Float3 verticalVector(0.0f, viewportHeight, 0.0f);
    const Float3 bottomLeft = cameraOrigin - horizontalVector / 2.0f - verticalVector / 2.0f - cameraLength;

    // Image
    constexpr int imageWidth = 400;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    constexpr int lastRowPixel = imageWidth - 1;
    constexpr int lastColPixel = imageHeight - 1;

    // World
    TraceableList world;
    world.Add(std::make_shared<Sphere>(Float3(0.0f, 0.0f, -1.0f), 0.5f));
    world.Add(std::make_shared<Sphere>(Float3(0.0f, -100.5f, -1.0f), 100.0f));

    // Render
    std::cout
        << "P3\n"
        << imageWidth << ' '
        << imageHeight << "\n255\n";

    for (int j = lastColPixel; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            const float uComponent = static_cast<float>(i) / lastRowPixel;
            const float vComponent = static_cast<float>(j) / lastColPixel;

            const Ray ray(cameraOrigin, bottomLeft + uComponent * horizontalVector + vComponent * verticalVector - cameraOrigin);
            Float3::WriteColor(std::cout, getRayColorFromWorld(ray, world));
        }
    }

    std::cerr << "\nDone.\n";
}
