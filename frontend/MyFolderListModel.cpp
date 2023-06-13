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
    return m_files.count();
}

QVariant MyFolderListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    const QFileInfo &fileInfo = m_files[index.row()];

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