#pragma once

#include "Vector3.h"
#include <iostream>

class Color : public Vector3
{
public:
    Color()
        : Vector3(0, 0, 0)
    {
    }

    Color(double x, double y, double z)
        : Vector3(x, y, z)
    {
    }

    double R() const;
    double G() const;
    double B() const;
};

#include "Color.inl"
