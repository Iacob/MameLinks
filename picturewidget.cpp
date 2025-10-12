#include "picturewidget.h"

#include <iostream>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QLabel>
#include <QPicture>
#include <QFile>
#include <QVBoxLayout>
#include <QPainter>

PictureWidget::PictureWidget(QWidget *parent)
    : QWidget{parent}
{
    this->setStyleSheet("background-color: grey");
    // QLabel *label = new QLabel(this);

    // QPixmap *pixmap = new QPixmap("/home/yong/temp/thunderbird.png");
    // // QPicture *picture = new QPicture();
    // // QFile *pictureFile = new QFile();
    // // pictureFile->open(QFile::ReadOnly);
    // // picture->load(pictureFile);
    // label->setPixmap(*pixmap);

    // QVBoxLayout *localLayout = new QVBoxLayout(this);
    // this->setLayout(localLayout);

    // localLayout->addWidget(label, INT_MAX, Qt::AlignVCenter);
}

void PictureWidget::resizeEvent(QResizeEvent *event) {
    std::cout << "resize height: " << event->size().height() << std::endl;
}

void PictureWidget::paintEvent(QPaintEvent *event) {
    std::cout << "paint event width:" << event->rect().width() << std::endl;
    QPainter painter(this);
    QPixmap pixmap(this->picPath[this->currentPicIdx]);
    painter.drawPixmap(0, 0, this->width(), this->height(), pixmap);
}

void PictureWidget::mousePressEvent(QMouseEvent *event) {
    std::cout << "click event" <<  std::endl;
    this->currentPicIdx = (this->currentPicIdx+1) % 2;
    this->update();
}
