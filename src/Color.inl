#pragma once

#include <iostream>

inline std::ostream& operator<<(std::ostream& ostream, const Color& color)
{
    const int redInt = static_cast<int>(255.999 * color.X());
    const int greenInt = static_cast<int>(255.999 * color.Y());
    const int blueInt = static_cast<int>(255.999 * color.Z());

    return ostream << redInt << ' ' << greenInt << ' ' << blueInt << '\n';
}

double Color::R() const
{
    return X();
}

double Color::G() const
{
    return Y();
}

double Color::B() const
{
    return Z();
}
