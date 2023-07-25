#pragma once

#include <sstream>

class LoggerImpl;

enum LogType
{
    INFO,
    WARNING,
    CRITICAL,
    FATAL
};

class LogStream
{
public:
    LogStream(LoggerImpl* logger, LogType type, const char* function);

    ~LogStream();

    template<typename T>
    LogStream& operator<<(const T& msg)
    {
        mSs << msg;
        return *this;
    }

private:
    std::stringstream mSs;
    LoggerImpl* mLogger;
    LogType mType;
    const char* mFunction;
};
