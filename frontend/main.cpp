#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QQmlContext>
#include <QDir>
#include <iostream>
#include "MyFolderListModel.h"

int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);
    try
    {
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
        parser.process(app);

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

    } catch (...)
    {
        std::cout << "Exception occurred" << std::endl;
    }
}
