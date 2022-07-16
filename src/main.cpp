#include <iostream>

#include "Double3.h"
#include "Double3.inl"
#include "Ray.h"

bool rayCollidesWithSphere(const Ray& ray, const Double3& center, double radius)
{
    const Double3 centerToOrigin = ray.Origin() - center;

    // Quadratic Formula
    const double a = Double3::Dot(ray.Direction(), ray.Direction());
    const double b = 2.0 * Double3::Dot(centerToOrigin, ray.Direction());
    const double c = Double3::Dot(centerToOrigin, centerToOrigin) - radius * radius;

    const double discriminant = b * b - 4 * a * c;
    return discriminant > 0;
}

Double3 getRayColor(const Ray& ray)
{
    const Double3 sphereCenter = Double3(0.0, 0.0, -1.0);
    constexpr double sphereRadius = 0.5;
    if (rayCollidesWithSphere(ray, sphereCenter, sphereRadius))
    {
        const Double3 red = Double3(1.0, 0.0, 0.0);
        return red;
    }

    // Lerp between colors for background
    const Double3 direction = Double3::Normalized(ray.Direction());
    const double length = 0.5 * (direction.Y() + 1.0);
    return (1.0 - length) * Double3(1.0, 1.0, 1.0) + (Double3(0.5, 0.7, 1.0) * length);
}

int main()
{
    constexpr double aspectRatio = 16.0 / 9.0;

    // Camera
    constexpr double viewportHeight = 2.0;
    constexpr double viewportWidth = viewportHeight * aspectRatio;
    constexpr double focalLength = 1.0;

    const Double3 cameraOrigin(0.0, 0.0, 0.0);
    const Double3 cameraLength(0.0, 0.0, focalLength);

    const Double3 horizontalVector(viewportWidth, 0.0, 0.0);
    const Double3 verticalVector(0.0, viewportHeight, 0.0);
    const Double3 bottomLeft = cameraOrigin - horizontalVector / 2 - verticalVector / 2 - cameraLength;

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
            const double uComponent = static_cast<double>(i) / lastRowPixel;
            const double vComponent = static_cast<double>(j) / lastColPixel;

            const Ray ray(cameraOrigin, bottomLeft + uComponent * horizontalVector + vComponent * verticalVector - cameraOrigin);
            Double3::WriteColor(std::cout, getRayColor(ray));
        }
    }

    std::cerr << "\nDone.\n";
}
