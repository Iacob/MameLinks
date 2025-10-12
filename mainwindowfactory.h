#ifndef MAINWINDOWFACTORY_H
#define MAINWINDOWFACTORY_H

#include "softwarelist.h"

class MainWindowFactory
{
public:
    SoftwareInfo *softwareInfos;
    int softwareCount;
    //
    MainWindowFactory();
    void displayMainWindow();
};

#endif // MAINWINDOWFACTORY_H
