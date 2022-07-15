#pragma once

#include "Vector3.h"
#include <iostream>

class Color : public Vector3
{
public:
    double R() const;
    double G() const;
    double B() const;
};

#include "Color.inl"
