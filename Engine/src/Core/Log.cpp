// #include "pch.h"
#include "Log.h"

namespace RealEngine
{
    std::shared_ptr<Logger> Log::m_CoreLogger;
    std::shared_ptr<Logger> Log::m_ClientLogger;

    void Log::Init()
    {
        m_CoreLogger = std::make_shared<Logger>();
        LOG_CORE_INFO("Log Initialized");
        m_ClientLogger = std::make_shared<Logger>();
        LOG_CLIENT_INFO("Log Initialized");
    }
}
