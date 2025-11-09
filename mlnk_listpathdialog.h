#ifndef MLNK_LISTPATHDIALOG_H
#define MLNK_LISTPATHDIALOG_H

#include <QWidget>
#include <QDialog>
#include <QCloseEvent>

#include "mlnk_dirlistselectordialog.h"

class MLNKListPathDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MLNKListPathDialog(QWidget *parent = nullptr);
private:
    MLNKDirListSelectorDialog *snapShotDirListSelector;
    MLNKDirListSelectorDialog *flyerShotDirListSelector;
    MLNKDirListSelectorDialog *cabinetShotDirListSelector;
    bool isConfigChanged = false;
protected:
    void closeEvent(QCloseEvent *event);
signals:
    void configChangedSignal();
signals:
};

#endif // MLNK_LISTPATHDIALOG_H
