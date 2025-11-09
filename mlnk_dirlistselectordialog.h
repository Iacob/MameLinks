#ifndef DIR_SELECTOR_H
#define DIR_SELECTOR_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>

#include "mlnk_configstore.h"

enum MLNKDirListSelectorMode {
    MLNKDirSelectorModeSnapshot,
    MLNKDirSelectorModeFlyer,
    MLNKDirSelectorModeCabinet
};

class MLNKDirListSelectorDialog : public QDialog
{
    Q_OBJECT
public:
    explicit MLNKDirListSelectorDialog(MLNKDirListSelectorMode mode, QWidget *parent = nullptr);
    ~MLNKDirListSelectorDialog();
    void openDirListConfig(MLNKDirListSelectorMode mode);
private:
    MLNKDirListSelectorMode selectorMode;
    QLabel *titleLabel;
    QWidget *saveDirBlock;
    QLabel *savePathLabel;
    QPushButton *selectSavePathButton;
    QPushButton *addNewDirButton;
    QPushButton *removeDirButton;
    QPushButton *moveDirUpButton;
    QPushButton *moveDirDownButton;
    QTableWidget *dirTableWidget;
    MLNKConfigStore configStore;
    QStringList dirList;
    void refreshDirList();
    void saveDirList();
signals:
public slots:
    void addNewDir();
    void removeDir();
};

#endif // DIR_SELECTOR_H
