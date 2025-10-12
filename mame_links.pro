QT = core \
    widgets xml

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp \
        mainwindowfactory.cpp \
        picturewidget.cpp \
        softdetailwidget.cpp \
        softwarefilelocator.cpp \
        softwarelist.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    MameLinksGlobal.h \
    mainwindowfactory.h \
    picturewidget.h \
    softdetailwidget.h \
    softwarefilelocator.h \
    softwarelist.h

RESOURCES += \
  application.qrc

DISTFILES += \
  res/MainWindow.css \
  res/mame0280.xml
