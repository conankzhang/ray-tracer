#include <iostream>

#include "Double3.h"
#include "Double3.inl"
#include "Ray.h"

double rayCollidesWithSphere(const Ray& ray, const Double3& center, double radius)
{
    const Double3 centerToOrigin = ray.Origin() - center;

    // Quadratic Formula
    const double a = ray.Direction().LengthSquared();
    const double halfB = Double3::Dot(centerToOrigin, ray.Direction());
    const double c = centerToOrigin.LengthSquared() - radius * radius;

    const double discriminant = halfB * halfB - a * c;
    if (discriminant < 0)
    {
        return -1.0;
    }
    else
    {
        return (-halfB - std::sqrt(discriminant)) / a;
    }
}

Double3 getRayColor(const Ray& ray)
{
    const Double3 sphereCenter = Double3(0.0, 0.0, -1.0);
    constexpr double sphereRadius = 0.5;

    double rayEnd = rayCollidesWithSphere(ray, sphereCenter, sphereRadius);
    if (rayEnd > 0.0)
    {
        // Return normal map of sphere
        const Double3 surfaceNormal = Double3::Normalized(ray.At(rayEnd) - sphereCenter);
        return 0.5 * Double3(surfaceNormal.X() + 1, surfaceNormal.Y() + 1, surfaceNormal.Z() + 1);
    }

    // Lerp between colors for background
    const Double3 direction = Double3::Normalized(ray.Direction());
    rayEnd = 0.5 * (direction.Y() + 1.0);
    return (1.0 - rayEnd) * Double3(1.0, 1.0, 1.0) + (Double3(0.5, 0.7, 1.0) * rayEnd);
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
