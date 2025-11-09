#include "mlnk_configstore.h"

#include <QSettings>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

#include "MameLinksGlobal.h"

MLNKConfigStore::MLNKConfigStore(QObject *parent)
    : QObject{parent}
{}

QString MLNKConfigStore::snapshotSaveDir() {
    QSettings settings(MAME_LINKS_CONST_ORG_NAME, MAME_LINKS_CONST_APP_NAME);
    settings.beginGroup("Global");
    QVariant snapshotSaveDirVar = settings.value("snapshot-save-dir");
    settings.endGroup();

    return snapshotSaveDirVar.toString();
}

QStringList MLNKConfigStore::snapshotDir() {
    QSettings settings(MAME_LINKS_CONST_ORG_NAME, MAME_LINKS_CONST_APP_NAME);
    settings.beginGroup("Global");
    QVariant snapshotDirVar = settings.value("snapshot-dir");
    settings.endGroup();

    QStringList resultList = snapshotDirVar.toStringList();
    return resultList;
}

void MLNKConfigStore::setSnapshotSaveDir(QString dir) {
    QSettings settings(MAME_LINKS_CONST_ORG_NAME, MAME_LINKS_CONST_APP_NAME);
    settings.beginGroup("Global");
    settings.setValue("snapshot-save-dir", QVariant::fromValue(dir));
    settings.endGroup();
}

void MLNKConfigStore::setSnapshotDir(QStringList dirList) {
    QSettings settings(MAME_LINKS_CONST_ORG_NAME, MAME_LINKS_CONST_APP_NAME);
    settings.beginGroup("Global");
    settings.setValue("snapshot-dir", QVariant::fromValue(dirList));
    settings.endGroup();
}
