#ifndef MLNK_CONFIGSTORE_H
#define MLNK_CONFIGSTORE_H

#include <QObject>

class MLNKConfigStore : public QObject
{
    Q_OBJECT
public:
    explicit MLNKConfigStore(QObject *parent = nullptr);
    QString snapshotSaveDir();
    QStringList snapshotDir();
    void setSnapshotSaveDir(QString dir);
    void setSnapshotDir(QStringList dirList);

signals:
};

#endif // MLNK_CONFIGSTORE_H
