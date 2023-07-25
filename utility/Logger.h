#pragma once

#include "implementations/logger/LoggerImpl.h"

extern LoggerImpl* g_logger;

inline LoggerImpl& Log(LogType type)
{
    return *g_logger;
}

#define Log(type)            \
    if (g_logger != nullptr) \
    g_logger->log(type, __PRETTY_FUNCTION__)

template<typename T>
void LogIfNull(T* object, const std::string& message)
{
    if (object == nullptr)
    {
        Log(WARNING) << message;
    }
}

inline void LogIfFalse(bool condition, const std::string& message)
{
    if (!condition)
    {
        Log(WARNING) << message;
    }
}

#define LogIfNullReturn(object, message) \
    if (object == nullptr)               \
    {                                    \
        Log(WARNING) << message;         \
        return;                          \
    }

#define LogIfFalseReturn(condition, message) \
    if (!condition)                          \
    {                                        \
        Log(WARNING) << message;             \
        return;                              \
    }

#define LogIfNullReturnValue(object, message, value) \
    if (object == nullptr)                           \
    {                                                \
        Log(WARNING) << message;                     \
        return value;                                \
    }

#define LogIfFalseReturnValue(condition, message, value) \
    if (!condition)                                      \
    {                                                    \
        Log(WARNING) << message;                         \
        return value;                                    \
    }
