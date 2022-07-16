#include <iostream>

#include "Float3.h"
#include "Float3.inl"
#include "Ray.h"

float rayCollidesWithSphere(const Ray& ray, const Float3& center, float radius)
{
    const Float3 centerToOrigin = ray.Origin() - center;

    // Quadratic Formula
    const float a = ray.Direction().LengthSquared();
    const float halfB = Float3::Dot(centerToOrigin, ray.Direction());
    const float c = centerToOrigin.LengthSquared() - radius * radius;

    const float discriminant = halfB * halfB - a * c;
    if (discriminant < 0.0f)
    {
        return -1.0f;
    }
    else
    {
        return (-halfB - std::sqrt(discriminant)) / a;
    }
}

Float3 getRayColor(const Ray& ray)
{
    const Float3 sphereCenter = Float3(0.0f, 0.0f, -1.0f);
    constexpr float sphereRadius = 0.5f;

    float rayEnd = rayCollidesWithSphere(ray, sphereCenter, sphereRadius);
    if (rayEnd > 0.0f)
    {
        // Return normal map of sphere
        const Float3 surfaceNormal = Float3::Normalized(ray.At(rayEnd) - sphereCenter);
        return 0.5f * Float3(surfaceNormal.X() + 1.0f, surfaceNormal.Y() + 1.0f, surfaceNormal.Z() + 1.0f);
    }

    // Lerp between colors for background
    const Float3 direction = Float3::Normalized(ray.Direction());
    rayEnd = 0.5f * (direction.Y() + 1.0f);
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

    // Render
    std::cout << "P3\n"
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
            Float3::WriteColor(std::cout, getRayColor(ray));
        }
    }

    std::cerr << "\nDone.\n";
}
