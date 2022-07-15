#include <iostream>

#include "Double3.h"
#include "Double3.inl"
#include "Ray.h"

Double3 getRayColor(const Ray& ray)
{
    const Double3 direction = Double3::Normalized(ray.Direction());
    const double length = 0.5 * (direction.Y() + 1.0);
    return (1.0 - length) * Double3(1.0, 1.0, 1.0) + (Double3(0.5, 0.7, 1.0) * length);
}

int main()
{
    // Image
    constexpr double aspectRatio = 16.0 / 9.0;
    constexpr int imageWidth = 400;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);

    // Camera
    constexpr double viewportHeight = 2.0;
    constexpr double viewportWidth = viewportHeight * aspectRatio;
    constexpr double focalLength = 1.0;

    const Double3 cameraOrigin(0.0, 0.0, 0.0);
    const Double3 cameraHorizontal(viewportWidth, 0.0, 0.0);
    const Double3 cameraVertical(0.0, viewportHeight, 0.0);
    const Double3 cameraLength(0.0, 0.0, focalLength);
    const Double3 bottomLeft = cameraOrigin - cameraHorizontal / 2 - cameraVertical / 2 - cameraLength;

    // Render
    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j >= 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            const double uComponent = static_cast<double>(i) / (imageWidth - 1);
            const double vComponent = static_cast<double>(j) / (imageHeight - 1);

            const Ray ray(cameraOrigin, bottomLeft + uComponent * cameraHorizontal + vComponent * cameraVertical - cameraOrigin);
            Double3::WriteColor(std::cout, getRayColor(ray));
        }
    }

    std::cerr << "\nDone.\n";
}
