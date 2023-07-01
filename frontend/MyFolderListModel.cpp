#include "MyFolderListModel.h"
#include "MyRunnable .h"

#include <qdebug.h>
#include <QThreadPool>
#include <QStringList>

#include <CompressorFactory.h>

MyFolderListModel::MyFolderListModel(QObject* parent)
    : QAbstractListModel(parent)
{
    connect(this, &MyFolderListModel::itemClicked, this, &MyFolderListModel::onItemClicked);
    initializerCompressor();
}

QString MyFolderListModel::folder() const
{
    return m_directory.absolutePath();
}

void MyFolderListModel::setFolder(const QString& folder)
{
    if (folder.isEmpty() || !m_directory.exists(folder))
        return;

    qDebug() << "Directory path:" << folder;

    beginResetModel();
    m_directory = QDir(folder);
    m_files = m_directory.entryInfoList(QStringList() << "*.bmp"
                                                      << "*.png"
                                                      << "*.barch",
        QDir::Files);
    for (int i = 0; i < m_files.size(); ++i)
    {
        m_encodingStatusList.append("");
    }
    endResetModel();

    emit folderChanged();
}

int MyFolderListModel::rowCount(const QModelIndex& parent) const
{
    Q_UNUSED(parent);

    int count = 0;

    for (const QFileInfo& fileInfo : m_files)
    {
        QString fileExtension = fileInfo.suffix().toLower();
        if (fileExtension == "bmp" || fileExtension == "png" || fileExtension == "barch")
        {
            count++;
        }
    }

    return count;
}

QHash<int, QByteArray> MyFolderListModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[FilePathRole] = "filePath";
    roles[FileExtensionRole] = "fileExtension";
    roles[FileSizeRole] = "fileSize";
    roles[FileEncodingStatusRole] = "fileEncodingStatus";
    return roles;
}

QVariant MyFolderListModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
        return QVariant();

    int filteredRow = 0;
    for (const QFileInfo& fileInfo : m_files)
    {
        QString fileExtension = fileInfo.suffix().toLower();
        if (fileExtension == "bmp" || fileExtension == "png" || fileExtension == "barch")
        {
            if (filteredRow == index.row())
            {
                switch (role)
                {
                    case FileNameRole :
                        return fileInfo.fileName();
                    case FilePathRole :
                        return fileInfo.filePath();
                    case FileExtensionRole :
                        return fileInfo.suffix();
                    case FileSizeRole :
                        return fileInfo.size();
                    case FileEncodingStatusRole :
                        return m_encodingStatusList.at(index.row());
                    default :
                        return QVariant();
                }
            }
            filteredRow++;
        }
    }

    return QVariant();
}

bool MyFolderListModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
    if (data(index, role) != value)
    {
        switch (role)
        {
            case FileEncodingStatusRole :
                m_encodingStatusList.replace(index.row(), value.toString());
                break;
        }

        emit dataChanged(index, index, QVector<int>() << role);
        return true;
    }
    return false;
}

void MyFolderListModel::onItemClicked(int index)
{
    qDebug() << "Item clicked:" << index;

    QRunnable* task = new MyRunnable([this, index]() {
        QString absoluteFilePath = data(this->index(index), FilePathRole).toString();
        QString fileName = data(this->index(index), FileNameRole).toString();
        QString filePath = data(this->index(index), FilePathRole).toString();
        QString fileExtension = data(this->index(index), FileExtensionRole).toString();

        if (fileExtension == "bmp")
        {
            qDebug() << "BMP file:" << absoluteFilePath;
            QMetaObject::invokeMethod(this, "updateData", Qt::QueuedConnection, Q_ARG(int, index), Q_ARG(QString, "Encoding"));

            auto rawData = m_compressor->loadRawImageFromFile(filePath.toStdString());
            auto encodedData = m_encoder->encode(rawData);
            m_compressor->saveEncodedDataToFile(absoluteFilePath.toStdString() + fileName.toStdString() + "_packed.barch", encodedData);

            QMetaObject::invokeMethod(this, "updateData", Qt::QueuedConnection, Q_ARG(int, index), Q_ARG(QString, ""));
        }
        else if (fileExtension == "barch")
        {
            qDebug() << "BARCH file:" << absoluteFilePath;
            QMetaObject::invokeMethod(this, "updateData", Qt::QueuedConnection, Q_ARG(int, index), Q_ARG(QString, "Decoding"));

            auto encodedData = m_compressor->loadEncodedDataFromFile(filePath.toStdString());
            auto rawData = m_decoder->decode(encodedData);
            m_compressor->saveRawImageToFile(absoluteFilePath.toStdString() + fileName.toStdString() + "_unpacked.bmp", rawData);

            QMetaObject::invokeMethod(this, "updateData", Qt::QueuedConnection, Q_ARG(int, index), Q_ARG(QString, ""));
        }
    });
    QThreadPool::globalInstance()->start(task);
}

void MyFolderListModel::initializerCompressor()
{
    CompressorFactory factory;
    m_compressor = factory.createCompressor();
    m_encoder = m_compressor->createEncoder();
    m_decoder = m_compressor->createDecoder();
}

void MyFolderListModel::updateData(int index, const QString& newValue)
{
    qDebug() << "Update data:" << index << newValue;
    setData(this->index(index), newValue, FileEncodingStatusRole);
}
