#include "MyFolderListModel.h"

#include <qdebug.h>

MyFolderListModel::MyFolderListModel(QObject *parent) : QAbstractListModel(parent) {
}

QString MyFolderListModel::folder() const {
    return m_directory.absolutePath();
}

void MyFolderListModel::setFolder(const QString &folder) {
    if (folder.isEmpty() || !m_directory.exists(folder))
        return;

    qDebug() << "Directory path:" << folder;

    beginResetModel();
    m_directory = QDir(folder);
    m_files = m_directory.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name);
    endResetModel();

    emit folderChanged();
}

int MyFolderListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);

    int count = 0;

    for (const QFileInfo &fileInfo: m_files) {
        QString fileExtension = fileInfo.suffix().toLower();
        if (fileExtension == "bmp" || fileExtension == "png" || fileExtension == "barch") {
            count++;
        }
    }

    return count;
}

QHash<int, QByteArray> MyFolderListModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[FileNameRole] = "fileName";
    roles[FilePathRole] = "filePath";
    roles[FileExtensionRole] = "fileExtension";
    roles[FileSizeRole] = "fileSize";
    return roles;
}

QVariant MyFolderListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    int filteredRow = 0;
    for (const QFileInfo &fileInfo: m_files) {
        QString fileExtension = fileInfo.suffix().toLower();
        if (fileExtension == "bmp" || fileExtension == "png" || fileExtension == "barch") {
            if (filteredRow == index.row()) {
                switch (role) {
                    case FileNameRole:
                        return fileInfo.fileName();
                    case FilePathRole:
                        return fileInfo.filePath();
                    case FileExtensionRole:
                        return fileInfo.suffix();
                    case FileSizeRole:
                        return fileInfo.size();
                    default:
                        return QVariant();
                }
            }
            filteredRow++;
        }
    }

    return QVariant();
}