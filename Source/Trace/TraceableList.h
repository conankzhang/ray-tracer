#pragma once

#include <memory>
#include <vector>

#include "Traceable.h"

class TraceableList final : public Traceable
{
public:
    void Clear();
    void Add(const std::shared_ptr<Traceable> traceable);

    virtual bool Trace(const Ray& ray, float rayStart, float rayEnd, HitResult& outResult) const override;

private:
    std::vector<std::shared_ptr<Traceable>> m_Traceables;
};

#include "TraceableList.inl"
