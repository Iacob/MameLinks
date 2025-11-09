#ifndef MLNK_MAINWINDOW_H
#define MLNK_MAINWINDOW_H

#include <QWidget>
#include <QTreeWidget>

#include "softwarelist.h"

class MLNKMainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MLNKMainWindow(QWidget *parent = nullptr);
public:
    SoftwareInfo *softwareInfos;
    int softwareCount;
    void showSoftwareList();
private:
    QTreeWidget *softwareTreeWidget;

signals:
};

#endif // MLNK_MAINWINDOW_H
