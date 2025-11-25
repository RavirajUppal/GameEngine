#include "pch.h"
#include "Logger.h"

namespace RealEngine
{
    static std::string CurrentTime()
    {
        std::time_t now = std::time(nullptr);
        char buffer[32];
        std::strftime(buffer, sizeof(buffer), "%H:%M:%S", std::localtime(&now));
        return buffer;
    }

    static const char *ToString(LogSource source)
    {
        switch (source)
        {
        case LogSource::Core:
            return "[Core]";
        case LogSource::Client:
            return "[Client]";
        default:
            return "[Unknown]";
        }
    }

    static const char *ToString(LogLevel level)
    {
        switch (level)
        {
        case LogLevel::Info:
            return "[Info]";
        case LogLevel::Warning:
            return "[Warning]";
        case LogLevel::Error:
            return "[Error]";
        default:
            return "[Unknown]";
        }
    }

    void Logger::Init(LogSource source)
    {
        Log(source, LogLevel::Info, "Initialized\n");
    }

    void Logger::Info(LogSource source, const std::string &message)
    {
        Log(source, LogLevel::Info, message);
    }

    void Logger::Warn(LogSource source, const std::string &message)
    {
        Log(source, LogLevel::Warning, message);
    }

    void Logger::Error(LogSource source, const std::string &message)
    {
        Log(source, LogLevel::Error, message);
    }

    void Logger::Log(LogSource source, LogLevel level, const std::string &message)
    {
        std::cout << CurrentTime() << " " << ToString(source) << " " << ToString(level) << " " << message << std::endl;
    }
}