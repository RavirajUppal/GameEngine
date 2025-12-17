#pragma once
#include <memory>
#include "Core.h"
#include "Logging/Logger.h"

#ifdef NDEBUG

#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)

#else

#if defined(IS_ENGINE_BUILD)
    #define LOG_INFO(...)     ::RealEngine::Log::GetLogger()->Info(RealEngine::LogSource::Core, __VA_ARGS__)
    #define LOG_WARN(...)     ::RealEngine::Log::GetLogger()->Warn(RealEngine::LogSource::Core, __VA_ARGS__)
    #define LOG_ERROR(...)    ::RealEngine::Log::GetLogger()->Error(RealEngine::LogSource::Core, __VA_ARGS__)
#elif defined(IS_GAME_BUILD)
    #define LOG_INFO(...)     ::RealEngine::Log::GetLogger()->Info(RealEngine::LogSource::Client, __VA_ARGS__)
    #define LOG_WARN(...)     ::RealEngine::Log::GetLogger()->Warn(RealEngine::LogSource::Client, __VA_ARGS__)
    #define LOG_ERROR(...)    ::RealEngine::Log::GetLogger()->Error(RealEngine::LogSource::Client, __VA_ARGS__)
#elif defined(IS_EDITOR_BUILD)
    #define LOG_INFO(...)     ::RealEngine::Log::GetLogger()->Info(RealEngine::LogSource::Editor, __VA_ARGS__)
    #define LOG_WARN(...)     ::RealEngine::Log::GetLogger()->Warn(RealEngine::LogSource::Editor, __VA_ARGS__)
    #define LOG_ERROR(...)    ::RealEngine::Log::GetLogger()->Error(RealEngine::LogSource::Editor, __VA_ARGS__)
#else
    #define LOG_INFO(...)     ::RealEngine::Log::GetLogger()->Info(RealEngine::LogSource::None, __VA_ARGS__)
    #define LOG_WARN(...)     ::RealEngine::Log::GetLogger()->Warn(RealEngine::LogSource::None, __VA_ARGS__)
    #define LOG_ERROR(...)    ::RealEngine::Log::GetLogger()->Error(RealEngine::LogSource::None, __VA_ARGS__)
#endif

// #define LOG_CORE_INFO(...)     ::RealEngine::Log::GetCoreLogger()->Info(RealEngine::LogSource::Core, __VA_ARGS__)
// #define LOG_CORE_WARN(...)     ::RealEngine::Log::GetCoreLogger()->Warn(RealEngine::LogSource::Core, __VA_ARGS__)
// #define LOG_CORE_ERROR(...)    ::RealEngine::Log::GetCoreLogger()->Error(RealEngine::LogSource::Core, __VA_ARGS__)
// #define LOG_CLIENT_INFO(...)   ::RealEngine::Log::GetClientLogger()->Info(RealEngine::LogSource::Client, __VA_ARGS__)
// #define LOG_CLIENT_WARN(...)   ::RealEngine::Log::GetClientLogger()->Warn(RealEngine::LogSource::Client, __VA_ARGS__)
// #define LOG_CLIENT_ERROR(...)  ::RealEngine::Log::GetClientLogger()->Error(RealEngine::LogSource::Client, __VA_ARGS__)

#endif

namespace RealEngine
{
    class REALENGINE_API Log
    {
    public:
        static void Init();
        static Logger* GetLogger() { return m_Logger.get(); }

    private:
        static std::unique_ptr<Logger> m_Logger;
    };
}