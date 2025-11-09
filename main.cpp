#include <QApplication>
#include <iostream>

//#include <mainwindow.h>
//#include "mainwindowfactory.h"
#include "softwarelist.h"

#include "mlnk_mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    // MainWindow mainWindow;
    // mainWindow.show();

    SoftwareInfo softwareInfos[50000];
    int softwareCount;

    std::cout << "开始加载软件列表" << std::endl;
    SoftwareList::readSoftwareList(softwareInfos, &softwareCount);
    std::cout << "软件列表加载完毕" << std::endl;

    // MainWindowFactory mainWindowFactory;
    // mainWindowFactory.softwareInfos = softwareInfos;
    // mainWindowFactory.softwareCount = softwareCount;
    // mainWindowFactory.displayMainWindow();

    MLNKMainWindow *mainWindow = new MLNKMainWindow();
    mainWindow->softwareInfos = softwareInfos;
    mainWindow->softwareCount = softwareCount;
    mainWindow->showSoftwareList();

    return a.exec();
}
