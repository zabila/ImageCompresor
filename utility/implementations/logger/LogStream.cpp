#include "LogStream.h"

#include "LoggerImpl.h"

LogStream::LogStream(LoggerImpl* logger, LogType type, const char* function)
    : mLogger(logger)
    , mType(type)
    , mFunction(function)
{
}

LogStream::~LogStream()
{
    if (!mSs.str().empty())
    {
        mLogger->write(mType, mFunction, mSs.str());
    }
}
