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

TraceableList GenerateWorld()
{
    TraceableList world;

    const auto groundMaterial = std::make_shared<Lambertian>(Float3(0.5f, 0.5f, 0.5f));
    world.Add(std::make_shared<Sphere>(Float3(0.0f, -1000.0f, 0.0f), 1000.0f, groundMaterial));

    const auto glassMaterial = std::make_shared<Dielectric>(1.5f);
    world.Add(std::make_shared<Sphere>(Float3(0.0f, 1.0f, 0.0f), 1.0f, glassMaterial));

    const auto centerMaterial = std::make_shared<Lambertian>(Float3(0.4f, 0.2f, 0.1f));
    world.Add(std::make_shared<Sphere>(Float3(-4.0f, 1.0f, 0.0f), 1.0f, centerMaterial));

    const auto rightMaterial = std::make_shared<Metal>(Float3(0.7f, 0.6f, 0.5f), 0.0f);
    world.Add(std::make_shared<Sphere>(Float3(4.0f, 1.0f, 0.0f), 1.0f, rightMaterial));

    const Float3 center(4.0f, 0.2f, 0.0f);

    for (int i = -11; i < 11; ++i)
    {
        for (int j = -11; j < 11; ++j)
        {
            const Float3 randomCenter(i + 0.9f * Math::RandomFloat(), 0.2f, j + 0.9f * Math::RandomFloat());
            const float distanceFromCenter = (randomCenter - center).Length();
            if (distanceFromCenter > 0.9f)
            {
                const float randomMaterial = Math::RandomFloat();
                if (randomMaterial < 0.8f)
                {
                    const Float3 randomColor = Math::RandomFloat3(0.0f, 1.0f) * Math::RandomFloat3(0.0f, 1.0f);
                    const auto lambertianMaterial = std::make_shared<Lambertian>(randomColor);
                    world.Add(std::make_shared<Sphere>(randomCenter, 0.2f, lambertianMaterial));
                }
                else if (randomMaterial < 0.95f)
                {
                    const Float3 randomColor = Math::RandomFloat3(0.5f, 1.0f);
                    const float randomFuzziness = Math::RandomFloat(0.0f, 0.5f);

                    const auto metalMaterial = std::make_shared<Metal>(randomColor, randomFuzziness);
                    world.Add(std::make_shared<Sphere>(randomCenter, 0.2f, metalMaterial));
                }
                else
                {
                    world.Add(std::make_shared<Sphere>(randomCenter, 0.2f, glassMaterial));
                }
            }
        }
    }

    return world;
}

int main()
{
    // Camera
    constexpr float aspectRatio = 3.0f / 2.0f;
    constexpr float verticalFov = 20.0f;
    constexpr float aperture = 0.1f;
    const Float3 cameraOrigin = Float3(13.0f, 2.0f, 3.0f);
    const Float3 focalPoint = Float3(0.0f, 0.0f, 0.0f);
    const Float3 cameraUp = Float3(0.0f, 1.0f, 0.0f);
    const float focalDistance = 10.0f;
    const Camera camera(cameraOrigin, focalPoint, cameraUp, verticalFov, aspectRatio, aperture, focalDistance);

    // Image
    constexpr int imageWidth = 1200;
    constexpr int imageHeight = static_cast<int>(imageWidth / aspectRatio);
    constexpr int lastRowPixel = imageWidth - 1;
    constexpr int lastColPixel = imageHeight - 1;
    constexpr int samplesPerPixel = 500;
    constexpr int maxBounceDepth = 50;

    TraceableList world = GenerateWorld();

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
