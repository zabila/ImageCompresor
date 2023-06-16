#pragma once

#include "ICompressor.h"
#include "IEncoder.h"
#include <QAbstractListModel>
#include <QDir>
#include <memory>

class MyFolderListModel : public QAbstractListModel {
Q_OBJECT
public:
    explicit MyFolderListModel(QObject *parent = nullptr);

    Q_PROPERTY(QString folder READ folder WRITE setFolder NOTIFY folderChanged)

    enum FolderListModelRoles {
        FileNameRole = Qt::UserRole + 1,
        FilePathRole,
        FileExtensionRole,
        FileSizeRole,
        FileEncodingStatusRole,
    };

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    QHash<int, QByteArray> roleNames() const override;

    QString folder() const;

    void setFolder(const QString &folder);

signals:

    void folderChanged();

    void itemClicked(int index);

private slots:

    void onItemClicked(int index);

    void updateData(int index, const QString &newValue);

private:
    void initializerCompressor();

    QDir m_directory;
    QFileInfoList m_files;
    QStringList m_encodingStatusList;

    std::shared_ptr<ICompressor> m_compressor;
    std::shared_ptr<IEncoder> m_encoder;
    std::shared_ptr<IDecoder> m_decoder;
};