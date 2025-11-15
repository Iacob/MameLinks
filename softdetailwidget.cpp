#include "softdetailwidget.h"

#include <iostream>
#include <QObject>
#include <QVBoxLayout>
#include <QTabBar>
#include <QPlainTextEdit>
#include <QPainter>
#include <QPixmap>

#include "softwarefilelocator.h"

SoftDetailWidget::SoftDetailWidget(QWidget* parent, int defaultTab): QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    tabBar = new QTabBar(this);
    tabBar->addTab("截图");
    tabBar->addTab("介绍");
    tabBar->setCurrentIndex(defaultTab); // 默认tab
    mainLayout->addWidget(tabBar, 0, Qt::AlignTop);

    QWidget *widget1 = new QWidget(this);
    //widget1.setMinimumSize(300, 200);
    mainLayout->addWidget(widget1);

    QVBoxLayout *widget1Layout = new QVBoxLayout(widget1);
    widget1->setLayout(widget1Layout);

    textArea = new QPlainTextEdit(widget1);
    textArea->setPlainText("aaa\nbbb\n");
    //textArea->setReadOnly(true);
    widget1Layout->addWidget(textArea);

    //textArea->setHidden(defaultTab != 1);
    this->setContentStatusByCurrentTab();

    const QAtomicPointer<QPlainTextEdit> atomicTextEditor(textArea);

    // QObject::connect(tabBar, &QTabBar::currentChanged, [=](int idx) {
    //     std::cout << "selected tab index: " << idx << std::endl;
    //     this->setContentStatusByCurrentTab();
    //     // if (idx == 0) {
    //     //     QPlainTextEdit* textEditor = atomicTextEditor.loadAcquire();
    //     //     textEditor->setHidden(true);
    //     // } else if (idx == 1) {
    //     //     QPlainTextEdit* textEditor = atomicTextEditor.loadAcquire();
    //     //     textEditor->setHidden(false);
    //     // }
    // });

    QObject::connect(tabBar, &QTabBar::currentChanged, this, &SoftDetailWidget::handlerTabChange);
}

void SoftDetailWidget::handlerTabChange(int tabIdx) {
    this->setContentStatusByCurrentTab();
}

void SoftDetailWidget::showDetailForSoftware(QString name) {
    QString snapshot = SoftwareFileLocator::findSnapshotPath(SoftwareFileLocator::FileTypeSnapShot, name);
    this->picturePath = snapshot;
    if (tabBar->currentIndex() == 0) {
        this->update();
    }
}

void SoftDetailWidget::setContentStatusByCurrentTab() {
    if (this->tabBar->currentIndex() == 1) {
        this->textArea->setHidden(false);
    } else {
        this->textArea->setHidden(true);
    }
    this->update();
}

void SoftDetailWidget::paintEvent(QPaintEvent *event) {
    //std::cout << "paint event width:" << event->rect().width() << " widget width:" << this->width() << std::endl;
    QPainter painter(this);
    if ((!this->picturePath.isEmpty()) && (this->tabBar->currentIndex() == 0)) {
        int topSpace = 45;
        int scaledHeight = event->rect().height() - topSpace;
        QPixmap pixmap(this->picturePath);
        int scaledWidth = (pixmap.width() * scaledHeight) / pixmap.height();
        int xpos = (event->rect().width() - scaledWidth)/2;
        painter.drawPixmap(xpos, topSpace, scaledWidth, event->rect().height(), pixmap);
    }
}
