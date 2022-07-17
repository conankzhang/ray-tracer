#pragma once

class Float3;
class Ray;
struct HitResult;

class Material
{
public:
    virtual bool Scatter(const Ray& incidentRay, const HitResult& hitResult, Float3& rayAttenuation, Ray& scatteredRay) const = 0;
};
