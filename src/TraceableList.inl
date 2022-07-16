#pragma once

inline void TraceableList::Clear()
{
    m_Traceables.clear();
}

inline void TraceableList::Add(const std::shared_ptr<Traceable> traceable)
{
    m_Traceables.push_back(traceable);
}
