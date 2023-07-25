#include "LoggerImpl.h"
#include "LogStream.h"

#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QMessageLogContext>
#include <QThread>
#include <qdebug.h>
#include <sstream>
#include <utility>

LoggerImpl::LoggerImpl(QString fileName)
    : qString(std::move(fileName))
{
    qFile.open(QIODevice::WriteOnly | QIODevice::Append);
}

LoggerImpl::~LoggerImpl()
{
    qFile.close();
}

LogStream LoggerImpl::log(LogType type, const char* function)
{
    return {this, type, function};
}

void LoggerImpl::write(LogType type, const char* function, const std::string& msg)
{
    QMutexLocker locker(&qMutex);

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeStr(dateTime.toString("dd-MM-yyyy HH:mm:ss:zzz"));
    QString typeStr;
    switch (type)
    {
        case INFO :
            typeStr = "INFO";
            break;
        case WARNING :
            typeStr = "WARNING";
            break;
        case CRITICAL :
            typeStr = "CRITICAL";
            break;
        case FATAL :
            typeStr = "FATAL";
            break;
    }
    QString functionStr(function);

    QString logMessage = "[" + timeStr + "][" + typeStr + "][" + functionStr + "] " + QString::fromStdString(msg);

    // Output to file
    //    QTextStream stream(&qFile);
    //    stream << logMessage << Qt::endl;

    // Output to console
    qInfo() << logMessage;
}

LoggerImpl* g_logger = nullptr;
