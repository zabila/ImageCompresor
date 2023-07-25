#pragma once

#include "LogStream.h"
#include <QString>
#include <QFile>
#include <QMutex>

class LoggerImpl
{
public:
    explicit LoggerImpl(QString fileName);

    ~LoggerImpl();

    LogStream log(LogType type, const char* function);

    void write(LogType type, const char* function, const std::string& msg);

private:
    QString qString;
    QFile qFile;
    QMutex qMutex;
};
