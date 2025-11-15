#include "mlnk_mainwindow.h"

#include <iostream>
#include <QFile>
#include <QVBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QSplitter>
#include <QTreeWidget>

#include "softdetailwidget.h"
#include "mlnk_listpathdialog.h"

MLNKMainWindow::MLNKMainWindow(QWidget *parent)
    : QWidget{parent}
{
    // 载入css
    QFile *qssFile = new QFile(":/res/MainWindow.css");
    qssFile->open(QFile::ReadOnly);
    //QString *qssStr = new QString(qssFile->readAll());
    QString qssStr = QString::fromUtf8(qssFile->readAll());
    qssFile->close();
    //
    this->setObjectName("mainWindow");
    this->setStyleSheet(qssStr);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    // 工具栏
    QFrame *toolbarWidget = new QFrame(this);
    toolbarWidget->setMinimumHeight(50);
    //toolbarWidget->setStyleSheet("background-color: yellow");
    toolbarWidget->setLayout(new QHBoxLayout(toolbarWidget));
    mainLayout->addWidget(toolbarWidget, 0, Qt::AlignTop);

    QPushButton *configPathButton = new QPushButton("🗀", toolbarWidget);
    toolbarWidget->layout()->addWidget(configPathButton);

    static_cast<QHBoxLayout*>(toolbarWidget->layout())->addWidget(configPathButton, 0, Qt::AlignLeft);
    static_cast<QHBoxLayout*>(toolbarWidget->layout())->addStretch(INT_MAX);

    // 主要内容窗口
    QSplitter *mainContentSplitterPane = new QSplitter(this);
    mainContentSplitterPane->setOrientation(Qt::Horizontal);
    mainLayout->addWidget(mainContentSplitterPane, INT_MAX);

    // 软件树形列表组件
    softwareTreeWidget = new QTreeWidget(this);
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

    // std::cout << "正在列出软件列表" << std::endl;
    // //
    // for (int i=0; i<this->softwareCount; i++) {
    //     QTreeWidgetItem *item = new QTreeWidgetItem(softwareTreeWidget);
    //     SoftwareInfo softwareInfo = this->softwareInfos[i];
    //     item->setText(0, softwareInfo.description);
    //     item->setText(1, softwareInfo.name);
    //     item->setText(2, softwareInfo.year);
    //     item->setText(3, softwareInfo.manufacturer);
    //     softwareTreeWidget->addTopLevelItem(item);
    //     // QString name;
    //     // QString description;
    //     // QString year;
    //     // QString manufacturer;
    // }
    // std::cout << "软件列表已列出" << std::endl;

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
    connect(softwareTreeWidget, &QTreeWidget::currentItemChanged, [=](QTreeWidgetItem *current, QTreeWidgetItem *previous) {
        if (previous != NULL) {
            std::cout << "previous:" << qPrintable(previous->text(1)) << std::endl;
        }
        if (current != nullptr) {
            std::cout << "current:" << qPrintable(current->text(1)) << std::endl;
            softwareDetailWidget1->showDetailForSoftware(current->text(1));
            softwareDetailWidget2->showDetailForSoftware(current->text(1));
        }
    });

    connect(configPathButton, &QPushButton::clicked, [=]() {
        MLNKListPathDialog *listPathDialog = new MLNKListPathDialog();
        listPathDialog->show();
    });


    mainContentSplitterPane->setStretchFactor(0, 0);
    mainContentSplitterPane->setStretchFactor(1, 1);
    mainContentSplitterPane->setOpaqueResize(true);
}

void MLNKMainWindow::showSoftwareList() {
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
    }
    std::cout << "软件列表已列出" << std::endl;
    this->show();
}
