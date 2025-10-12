#include "softwarefilelocator.h"

#include <QString>
#include <QSettings>
#include <QDir>
#include <QStringList>
#include <QString>
#include "MameLinksGlobal.h"

SoftwareFileLocator::SoftwareFileLocator() {}

QString SoftwareFileLocator::findSnapshotPath(SoftwareFileLocator::FileType fileType, QString software) {
    QSettings settings(MAME_LINKS_CONST_ORG_NAME, MAME_LINKS_CONST_APP_NAME);
    settings.beginGroup("Global");
    QVariant snapshotDirVar = settings.value("snapshot-dir");
    QString snapshotDir = snapshotDirVar.toString();
    settings.endGroup();

    if (fileType == FileTypeSnapShot) {
        QDir dir1(snapshotDir);
        QStringList nameFilter;
        nameFilter << (software + ".png") << (software + ".jpg");
        //QStringList list1 = dir1.entryList(nameFilter, QDir::Dirs | QDir::Files, QDir::Name);
        QFileInfoList fileInfoList1 = dir1.entryInfoList(nameFilter, QDir::Dirs | QDir::Files);
        if (fileInfoList1.count() > 0) {
            return fileInfoList1.at(0).absoluteFilePath();
        }
    }
    return QString();
}
