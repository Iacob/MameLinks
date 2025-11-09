#include "mlnk_listpathdialog.h"
#include "mlnk_configstore.h"
#include "mlnk_dirlistselectordialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QCloseEvent>

MLNKListPathDialog::MLNKListPathDialog(QWidget *parent)
    : QDialog{parent}
    ,snapShotDirListSelector(new MLNKDirListSelectorDialog(MLNKDirSelectorModeSnapshot, this))
    ,flyerShotDirListSelector(new MLNKDirListSelectorDialog(MLNKDirSelectorModeFlyer, this))
    ,cabinetShotDirListSelector(new MLNKDirListSelectorDialog(MLNKDirSelectorModeCabinet, this))
{
    this->setLayout(new QVBoxLayout);

    MLNKConfigStore store;

    QStringList snapShotDirList = store.snapshotDir();

    QString snapshotStr = "截图";
    snapshotStr += "\n    保存路径:";
    snapshotStr += "/tmp";
    snapshotStr += "\n    ";
    snapshotStr += "存档路径:\n        ";
    snapshotStr += snapShotDirList.join("\n        ");

    QPushButton *snapshotDirSelectButton = new QPushButton(snapshotStr, this);
    QFont defaultFont1 = snapshotDirSelectButton->font();
    snapshotDirSelectButton->setStyleSheet("text-align: left");

    static_cast<QVBoxLayout*>(this->layout())->addWidget(snapshotDirSelectButton, 0, Qt::AlignTop);



    static_cast<QVBoxLayout*>(this->layout())->addWidget(new QLabel("宣传画", this), 0, Qt::AlignTop);
    static_cast<QVBoxLayout*>(this->layout())->addWidget(new QLabel("    aa\n    bb \n    cc", this), 0, Qt::AlignTop);

    static_cast<QVBoxLayout*>(this->layout())->addWidget(new QLabel("外观", this), 0, Qt::AlignTop);
    static_cast<QVBoxLayout*>(this->layout())->addWidget(new QLabel("    aa\n    bb \n    cc", this), 0, Qt::AlignTop);

    static_cast<QVBoxLayout*>(this->layout())->addStretch(INT_MAX);

    this->resize(800, -1);

    connect(snapshotDirSelectButton, &QPushButton::clicked, this, [&](){
        snapShotDirListSelector->openDirListConfig(MLNKDirSelectorModeSnapshot);
    });
}

void MLNKListPathDialog::closeEvent(QCloseEvent *event) {
    emit configChangedSignal();
}
