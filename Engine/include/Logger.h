#pragma once
#include <string>
#include <sstream>

namespace RealEngine
{
    enum class LogLevel
    {
        Info,
        Warning,
        Error
    };

    enum class LogSource
    {
        Core,
        Client
    };

    class Logger
    {
    public:
        static void Init(LogSource source);

        static void Info(LogSource source, const std::string &message);
        static void Warn(LogSource source, const std::string &message);
        static void Error(LogSource source, const std::string &message);

        template <typename T>
        static void InfoT(LogSource source, const T &value)
        {
            std::ostringstream ss;
            ss << value;
            Info(source, ss.str());
        }

        template <typename T>
        static void WarnT(LogSource source, const T &value)
        {
            std::ostringstream ss;
            ss << value;
            Warn(source, ss.str());
        }

        template <typename T>
        static void ErrorT(LogSource source, const T &value)
        {
            std::ostringstream ss;
            ss << value;
            Error(source, ss.str());
        }

    private:
        static void Log(LogSource source, LogLevel level, const std::string &message);
    };
}
