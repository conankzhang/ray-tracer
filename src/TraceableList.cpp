#include "TraceableList.h"

#include "HitResult.h"

bool TraceableList::Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const
{
    HitResult result;

    bool traceHit = false;
    float closestRay = rayEnd;
    for (const std::shared_ptr<Traceable>& traceable : m_Traceables)
    {
        if (traceable->Trace(ray, rayStart, closestRay, result))
        {
            traceHit = true;
            closestRay = result.m_rayEnd;
            outResult = result;
        }
    }

    return traceHit;
}
