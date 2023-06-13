#pragma once

#include <QAbstractListModel>
#include <QDir>

class MyFolderListModel : public QAbstractListModel {
Q_OBJECT
public:
    explicit MyFolderListModel(QObject *parent = nullptr);

    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)

    enum FolderListModelRoles {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileExtensionRole,
        FileSizeRole
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override;

    QString folder() const;

    void setFolder(const QString &folder);

signals:

    void folderChanged();

private:
    QDir m_directory;
    QFileInfoList m_files;
};