#pragma once

class Ray;
struct HitResult;

class Traceable
{
public:
    virtual bool Trace(const Ray& ray, double rayStart, double rayEnd, HitResult& outResult) const = 0;
};
