#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QDir>
#include <iostream>
#include <qcommandlineoption.h>
#include "ImageCompressor.h"
#include "MyFolderListModel.h"
#include <QLoggingCategory>
#include "Logger.h"

void process_file(const QCommandLineParser& parser, const QCommandLineOption& file_option);

int main(int argc, char* argv[])
{
    g_logger = new LoggerImpl("log.txt");
    QLoggingCategory::setFilterRules("*.info=true");
    try
    {
        Log(INFO) << "Start project";
        QGuiApplication app(argc, argv);
        QCoreApplication::setApplicationName("Image Compressor");
        QCoreApplication::setApplicationVersion("1.0");
        QQmlApplicationEngine engine;

        QCommandLineParser parser;
        parser.setApplicationDescription("Helper");
        parser.addHelpOption();
        parser.addVersionOption();

        QCommandLineOption targetDirectoryOption(QStringList() << "d"
                                                               << "directory",
            QCoreApplication::translate("main", "start from directory path <directory>."), QCoreApplication::translate("main", "directory"));
        parser.addOption(targetDirectoryOption);

        QCommandLineOption targetFileOption(QStringList() << "f"
                                                          << "file",
            QCoreApplication::translate("main", "start from file path <file>."), QCoreApplication::translate("main", "file"));

        parser.addOption(targetFileOption);

        parser.process(app);

        const bool isSetFileOption = parser.isSet(targetFileOption);

        if (isSetFileOption)
        {
            Log(INFO) << "Found file optionns";
            process_file(parser, targetFileOption);
            return 0;
        }
        else
        {
            Log(WARNING) << "File don't found";
        }

        MyFolderListModel folderModelWrapper;
        QString directory = parser.values(targetDirectoryOption).value(0);
        if (directory.isEmpty() || !QDir(directory).exists())
            directory = QDir::currentPath();
        folderModelWrapper.setFolder(directory);

        engine.rootContext()->setContextProperty("myFolderModel", &folderModelWrapper);
        engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

        if (engine.rootObjects().isEmpty())
            return -1;

        return app.exec();

    } catch (std::exception& ext)
    {
        Log(FATAL) << "Exception: " << ext.what();
    }
    delete g_logger;
    g_logger = nullptr;
}

void process_file(const QCommandLineParser& parser, const QCommandLineOption& file_option)
{
    const QString q_file_from_option = parser.values(file_option).value(0);
    if (q_file_from_option.isEmpty() || !QFile(q_file_from_option).exists())
    {
        Log(FATAL) << "File don't exists or empty";
        return;
    }

    const QFileInfo q_file_info(q_file_from_option);
    const QString q_full_file_path = q_file_info.absoluteFilePath();

    std::unique_ptr<ImageCompressor> compresor = std::make_unique<ImageCompressor>();
    std::shared_ptr<IEncoder> encoder = compresor->createEncoder();

    const std::string file_full_path = q_full_file_path.toStdString();
    Log(INFO) << "File found: " << file_full_path;

    const RawImageData imange_data = compresor->loadRawImageFromFile(file_full_path);

    Log(INFO) << "Image data loaded: " << imange_data.width << "x" << imange_data.height << "x";

    encoder->encode(imange_data);
}
