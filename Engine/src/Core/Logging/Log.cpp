// #include "pch.h"
#include "Logging/Log.h"

namespace RealEngine
{
    std::unique_ptr<Logger> Log::m_Logger;

    void Log::Init()
    {
        m_Logger = std::make_unique<Logger>();
        LOG_INFO("Log Initialized");
    }
}
