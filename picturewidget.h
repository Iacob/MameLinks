#ifndef PICTUREWIDGET_H
#define PICTUREWIDGET_H

#include <QWidget>

class PictureWidget : public QWidget
{
    //Q_OBJECT
public:
    explicit PictureWidget(QWidget *parent = nullptr);

protected:
    void resizeEvent(QResizeEvent *event);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    QString picPath[2] = {"/home/yong/temp/thunderbird.png", "/home/yong/temp/r-type.png"};
    int currentPicIdx = 0;

signals:
};

#endif // PICTUREWIDGET_H
