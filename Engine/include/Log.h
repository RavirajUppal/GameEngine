#pragma once
#include <memory>
#include "Core.h"
#include "Logger.h"

#ifdef NDEBUG

#define LOG_CORE_INFO(...)
#define LOG_CORE_WARN(...)
#define LOG_CORE_ERROR(...)
#define LOG_CLIENT_INFO(...)
#define LOG_CLIENT_WARN(...)
#define LOG_CLIENT_ERROR(...)

#else

#define LOG_CORE_INFO(...)     ::RealEngine::Log::GetCoreLogger()->Info(RealEngine::LogSource::Core, __VA_ARGS__)
#define LOG_CORE_WARN(...)     ::RealEngine::Log::GetCoreLogger()->Warn(RealEngine::LogSource::Core, __VA_ARGS__)
#define LOG_CORE_ERROR(...)    ::RealEngine::Log::GetCoreLogger()->Error(RealEngine::LogSource::Core, __VA_ARGS__)
#define LOG_CLIENT_INFO(...)   ::RealEngine::Log::GetClientLogger()->Info(RealEngine::LogSource::Client, __VA_ARGS__)
#define LOG_CLIENT_WARN(...)   ::RealEngine::Log::GetClientLogger()->Warn(RealEngine::LogSource::Client, __VA_ARGS__)
#define LOG_CLIENT_ERROR(...)  ::RealEngine::Log::GetClientLogger()->Error(RealEngine::LogSource::Client, __VA_ARGS__)

#endif

namespace RealEngine
{
    class REALENGINE_API Log
    {
    public:
        static void Init();
        static std::shared_ptr<Logger> &GetCoreLogger() { return m_CoreLogger; }
        static std::shared_ptr<Logger> &GetClientLogger() { return m_ClientLogger; }

    private:
        static std::shared_ptr<Logger> m_CoreLogger;
        static std::shared_ptr<Logger> m_ClientLogger;
    };
}