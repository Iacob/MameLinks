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
protected:
    void setContentStatusByCurrentTab();
    void paintEvent(QPaintEvent *event);
private:
    QTabBar *tabBar;
    QPlainTextEdit *textArea;
    QString picturePath;
    QString software;
public slots:
    void handlerTabChange(int tabIdx);
    void showDetailForSoftware(QString name);
};

#endif // SOFTDETAILWIDGET_H
