#include "mainwindowfactory.h"
#include "softdetailwidget.h"
//#include "softwarefilelocator.h"

#include <iostream>

#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSplitter>
#include <QFrame>
#include <QTreeWidget>
#include <QTabWidget>
#include <QFile>
#include <QString>
#include <QStringList>
#include <QTreeWidgetItem>

MainWindowFactory::MainWindowFactory() {}

void MainWindowFactory::displayMainWindow() {

    // 载入css
    QFile *qssFile = new QFile(":/res/MainWindow.css");
    qssFile->open(QFile::ReadOnly);
    //QString *qssStr = new QString(qssFile->readAll());
    QString qssStr = QString::fromUtf8(qssFile->readAll());
    qssFile->close();

    QWidget *mainWindow = new QWidget();
    mainWindow->setObjectName("mainWindow");
    mainWindow->setStyleSheet(qssStr);

    QVBoxLayout *mainLayout = new QVBoxLayout(mainWindow);
    mainWindow->setLayout(mainLayout);

    // 工具栏
    QFrame *toolbarWidget = new QFrame(mainWindow);
    toolbarWidget->setMinimumHeight(50);
    toolbarWidget->setStyleSheet("background-color: yellow");
    mainLayout->addWidget(toolbarWidget, 0, Qt::AlignTop);

    // 主要内容窗口
    QSplitter *mainContentSplitterPane = new QSplitter(mainWindow);
    mainContentSplitterPane->setOrientation(Qt::Horizontal);
    mainLayout->addWidget(mainContentSplitterPane, INT_MAX);

    // 软件树形列表组件
    QTreeWidget *softwareTreeWidget = new QTreeWidget(mainWindow);
    softwareTreeWidget->setObjectName("softwareTreeWidget");
    mainContentSplitterPane->addWidget(softwareTreeWidget);

    QStringList columnLabels;
    columnLabels += "description";
    columnLabels += "name";
    columnLabels += "year";
    columnLabels += "manufacturer";
    softwareTreeWidget->setColumnCount(columnLabels.count());
    softwareTreeWidget->setHeaderLabels(columnLabels);
    //softwareTreeWidget.set
    softwareTreeWidget->setSortingEnabled(true);
    softwareTreeWidget->sortItems(0, Qt::AscendingOrder);

    std::cout << "正在列出软件列表" << std::endl;
    //
    for (int i=0; i<this->softwareCount; i++) {
        QTreeWidgetItem *item = new QTreeWidgetItem(softwareTreeWidget);
        SoftwareInfo softwareInfo = this->softwareInfos[i];
        item->setText(0, softwareInfo.description);
        item->setText(1, softwareInfo.name);
        item->setText(2, softwareInfo.year);
        item->setText(3, softwareInfo.manufacturer);
        softwareTreeWidget->addTopLevelItem(item);
        // QString name;
        // QString description;
        // QString year;
        // QString manufacturer;
    }
    std::cout << "软件列表已列出" << std::endl;

    softwareTreeWidget->setColumnWidth(0, 500);

    // 软件详情组件
    QSplitter *softwareDetailSplitterPane = new QSplitter(mainContentSplitterPane);
    softwareDetailSplitterPane->setOrientation(Qt::Vertical);
    mainContentSplitterPane->addWidget(softwareDetailSplitterPane);

    // 软件详情上
    SoftDetailWidget *softwareDetailWidget1 = new SoftDetailWidget(softwareDetailSplitterPane);
    softwareDetailSplitterPane->addWidget(softwareDetailWidget1);
    // QTabWidget *softwareDetailWidget1 = new QTabWidget(softwareDetailSplitterPane);
    // softwareDetailSplitterPane->addWidget(softwareDetailWidget1);

    // QWidget *snapshotWidget1 = new QWidget(softwareDetailWidget1);
    // softwareDetailWidget1->addTab(snapshotWidget1, "截图");

    // 软件详情下
    SoftDetailWidget *softwareDetailWidget2 = new SoftDetailWidget(softwareDetailSplitterPane, 1);
    softwareDetailSplitterPane->addWidget(softwareDetailWidget2);

    // QTabWidget *softwareDetailWidget2 = new QTabWidget(softwareDetailSplitterPane);
    // softwareDetailSplitterPane->addWidget(softwareDetailWidget2);

    // QWidget *snapshotWidget2 = new QWidget(softwareDetailWidget2);
    // softwareDetailWidget2->addTab(snapshotWidget2, "截图二");

    // QObject::connect(softwareTreeWidget, &QTreeWidget::itemActivated, [=](QTreeWidgetItem *item, int column) {
    //     std::cout << column << " " << qPrintable(item->text(1)) << std::endl;
    // });
    QObject::connect(softwareTreeWidget, &QTreeWidget::currentItemChanged, [=](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
        if (previous != NULL) {
            std::cout << "previous:" << qPrintable(previous->text(1)) << std::endl;
        }
        if (current != nullptr) {
            std::cout << "current:" << qPrintable(current->text(1)) << std::endl;
            softwareDetailWidget1->showDetailForSoftware(current->text(1));
        }
    });


    mainContentSplitterPane->setStretchFactor(0, 0);
    mainContentSplitterPane->setStretchFactor(1, 1);
    mainContentSplitterPane->setOpaqueResize(true);

    mainWindow->show();
}
