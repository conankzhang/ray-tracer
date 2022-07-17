#include <iostream>

#include "Camera/Camera.h"
#include "Materials/Dielectric.h"
#include "Materials/Lambertian.h"
#include "Materials/Metal.h"
#include "Math/Float3.h"
#include "Math/Math.h"
#include "Math/Random.h"
#include "Math/Ray.h"
#include "Math/Sphere.h"
#include "Trace/HitResult.h"
#include "Trace/TraceableList.h"

void PrintVector(std::ostream& ostream, const Float3& vector)
{
    ostream << "X: " << vector.X() << " Y: " << vector.Y() << " Z: " << vector.Z();
}

void WriteColor(std::ostream& ostream, const Float3& color, int samplesPerPixel)
{
    const float scale = 1.0f / samplesPerPixel;

    const float red = std::sqrt(color.R() * scale);
    const float green = std::sqrt(color.G() * scale);
    const float blue = std::sqrt(color.B() * scale);

    const int redInt = static_cast<int>(256 * Math::Clamp(red, 0.0f, 0.999f));
    const int greenInt = static_cast<int>(256 * Math::Clamp(green, 0.0f, 0.999f));
    const int blueInt = static_cast<int>(256 * Math::Clamp(blue, 0.0f, 0.999f));

    ostream << redInt << ' ' << greenInt << ' ' << blueInt << '\n';
}

Float3 getRayColorFromWorld(const Ray& ray, const TraceableList& world, int depth)
{
    if (depth <= 0)
    {
        // Guard against stack overflow
        return Float3(0.0f, 0.0f, 0.0f);
    }

    HitResult result;
    if (world.Trace(ray, 0.001f, Math::s_Infinity, result))
    {
        Ray scatteredRay;
        Float3 attenuation;
        if (result.m_Material->ScatterRay(ray, result, attenuation, scatteredRay))
        {
            return attenuation * getRayColorFromWorld(scatteredRay, world, depth - 1);
        }

        return Float3(0.0f, 0.0f, 0.0f);
    }

    // Lerp between colors for background
    const Float3 direction = Float3::Normalized(ray.Direction());
    const float rayEnd = 0.5f * (direction.Y() + 1.0f);
    return (1.0f - rayEnd) * Float3(1.0f, 1.0f, 1.0f) + (Float3(0.5f, 0.7f, 1.0f) * rayEnd);
}

int main()
{
    constexpr float aspectRatio = 16.0f / 9.0f;

    const Camera camera(aspectRatio);

    // Image
    constexpr int imageWidth = 400;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    constexpr int lastRowPixel = imageWidth - 1;
    constexpr int lastColPixel = imageHeight - 1;
    constexpr int samplesPerPixel = 100;
    constexpr int maxBounceDepth = 50;

    // World
    TraceableList world;

    const auto groundMaterial = std::make_shared<Lambertian>(Float3(0.8f, 0.8f, 0.0f));
    world.Add(std::make_shared<Sphere>(Float3(0.0f, -100.5f, -1.0f), 100.0f, groundMaterial));

    const auto centerMaterial = std::make_shared<Dielectric>(1.5f);
    world.Add(std::make_shared<Sphere>(Float3(0.0f, 0.0f, -1.0f), 0.5f, centerMaterial));

    const auto leftMaterial = std::make_shared<Dielectric>(1.5f);
    world.Add(std::make_shared<Sphere>(Float3(-1.0f, 0.0f, -1.0f), 0.5f, leftMaterial));

    const auto rightMaterial = std::make_shared<Metal>(Float3(0.8f, 0.6f, 0.2f), 1.0f);
    world.Add(std::make_shared<Sphere>(Float3(1.0f, 0.0f, -1.0f), 0.5f, rightMaterial));

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
            Float3 pixelColor(0.0f, 0.0f, 0.0f);
            for (int sample = 0; sample < samplesPerPixel; ++sample)
            {
                const float u = static_cast<float>(i + Math::RandomFloat()) / lastRowPixel;
                const float v = static_cast<float>(j + Math::RandomFloat()) / lastColPixel;

                const Ray cameraRay = camera.GetRayForPixel(u, v);
                pixelColor += getRayColorFromWorld(cameraRay, world, maxBounceDepth);
            }

            WriteColor(std::cout, pixelColor, samplesPerPixel);
        }
    }

    std::cerr << "\nDone.\n";
}
