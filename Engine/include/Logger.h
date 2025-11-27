#pragma once

#include "Core.h"
#include <string>
#include <sstream>

namespace RealEngine
{
    enum class LogLevel
    {
        None,
        Info,
        Warning,
        Error
    };

    enum class LogSource
    {
        None,
        Core,
        Client
    };

    class REALENGINE_API Logger
    {
    public:
        static void Init(LogSource source);

        template <typename T>
        static void InsertIntoString(std::string &msg, T&& value)
        {
            std::ostringstream ss;
            ss << std::forward<T>(value);
            size_t pos = msg.find("{}");
            if (pos != std::string::npos){
                msg.replace(pos, 2, ss.str());
            }
        }

        template <typename... Args>
        static void FormatString(std::string &msg, Args&&... args)
        {
            (InsertIntoString(msg, std::forward<Args>(args)), ...);
        }

        template <typename... Args>
        static std::string GetMessage(std::string_view str, Args&&... args)
        {
            std::string msg(str);
            FormatString(msg, std::forward<Args>(args)...);
            return msg;
        }

        template <typename... Args>
        static void Info(LogSource source, std::string_view str, Args&&... args)
        {
            std::string msg = GetMessage(str, std::forward<Args>(args)...);
            LogInfo(source, msg);
        }

        template <typename... Args>
        static void Warn(LogSource source, std::string_view str, Args&&... args)
        {
            std::string msg = GetMessage(str, std::forward<Args>(args)...);
            LogWarn(source, msg);
        }

        template <typename... Args>
        static void Error(LogSource source, std::string_view str, Args&&... args)
        {
            std::string msg = GetMessage(str, std::forward<Args>(args)...);
            LogError(source, msg);
        }

    private:
        static void LogInfo(LogSource source, const std::string &message);
        static void LogWarn(LogSource source, const std::string &message);
        static void LogError(LogSource source, const std::string &message);
        static void Log(LogSource source, LogLevel level, const std::string &message);
    };
}
