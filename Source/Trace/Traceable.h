#pragma once

class Ray;
struct HitResult;

class Traceable
{
public:
    virtual bool Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const = 0;
};
