#ifndef SOFTDETAILWIDGET_H
#define SOFTDETAILWIDGET_H

#include <QWidget>
#include <QTabBar>
#include <QPlainTextEdit>
#include <QPaintEvent>

class SoftDetailWidget: public QWidget
{
public:
    SoftDetailWidget(QWidget* parentwidget = nullptr, int defaultTab = 0);
    void showDetailForSoftware(QString name);
protected:
    void setContentStatusByCurrentTab();
    void paintEvent(QPaintEvent *event);
private:
    QTabBar *tabBar;
    QPlainTextEdit *textArea;
    QString picturePath;
    QString software;
};

#endif // SOFTDETAILWIDGET_H
