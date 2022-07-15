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
    constexpr int imageWidth = 256;
    constexpr int imageHeight = 256;

    std::cout << "P3\n"
              << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j > 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            const double red = static_cast<double>(i) / (imageWidth - 1);
            const double green = static_cast<double>(j) / (imageHeight - 1);
            constexpr double blue = 0.25;

            Double3 color(red, green, blue);
            WriteColor(std::cout, color);
        }
    }

    std::cerr << "\nDone.\n";
}
