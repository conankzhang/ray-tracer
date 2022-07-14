#include <iostream>

int main()
{
    constexpr int imageWidth = 256;
    constexpr int imageHeight = 256;

    std::cout << "P3\n" << imageWidth << ' ' << imageHeight << "\n255\n";

    for (int j = imageHeight - 1; j > 0; --j)
    {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < imageWidth; ++i)
        {
            const double red = static_cast<double>(i) / (imageWidth - 1);
            const double green = static_cast<double>(j) / (imageHeight - 1);
            constexpr double blue = 0.25;

            const int redInt = static_cast<int>(255.999 * red);
            const int greenInt = static_cast<int>(255.999 * green);
            const int blueInt = static_cast<int>(255.999 * blue);

            std::cout << redInt << ' ' << greenInt << ' ' << blueInt << '\n';
        }
    }

    std::cerr << "\nDone.\n";
}
