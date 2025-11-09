#include "mlnk_dirlistselectordialog.h"
#include "mlnk_configstore.h"

#include <iostream>
#include <QString>
#include <QLabel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QFileDialog>
#include <QHeaderView>

MLNKDirListSelectorDialog::MLNKDirListSelectorDialog(MLNKDirListSelectorMode mode, QWidget *parent)
    : QDialog{parent}, selectorMode(mode), configStore(MLNKConfigStore(this))
{
    this->setLayout(new QVBoxLayout(this));
    QString title;
    switch (mode) {
    case MLNKDirSelectorModeSnapshot:
        title = "请选择截图目录";
        break;
    default:
        title = "请选择未知目录";
        break;
    }
    titleLabel = new QLabel(title, this);
    static_cast<QVBoxLayout*>(this->layout())->addWidget(titleLabel, 0, Qt::AlignTop);

    saveDirBlock = new QWidget(this);
    saveDirBlock->setLayout(new QHBoxLayout(saveDirBlock));
    static_cast<QVBoxLayout*>(this->layout())->addWidget(saveDirBlock, 0, Qt::AlignTop);

    static_cast<QHBoxLayout*>(saveDirBlock->layout())->addWidget(new QLabel("保存目录", saveDirBlock), 0, Qt::AlignLeft);

    savePathLabel = new QLabel("/home", saveDirBlock);
    static_cast<QHBoxLayout*>(saveDirBlock->layout())->addWidget(savePathLabel, INT_MAX, Qt::AlignHCenter);

    selectSavePathButton = new QPushButton("选择目录", saveDirBlock);
    static_cast<QHBoxLayout*>(saveDirBlock->layout())->addWidget(selectSavePathButton, 0, Qt::AlignRight);

    dirTableWidget = new QTableWidget(this);
    dirTableWidget->setColumnCount(1);
    dirTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dirTableWidget->setSelectionMode(QTableWidget::SingleSelection);
    static_cast<QVBoxLayout*>(this->layout())->addWidget(dirTableWidget, INT_MAX);

    QWidget *dirOpPanelBlock = new QWidget(this);
    dirOpPanelBlock->setLayout(new QHBoxLayout(dirOpPanelBlock));
    static_cast<QVBoxLayout*>(this->layout())->addWidget(dirOpPanelBlock, 0, Qt::AlignBottom);

    addNewDirButton = new QPushButton("+", dirOpPanelBlock);
    removeDirButton = new QPushButton("-", dirOpPanelBlock);
    moveDirUpButton = new QPushButton("⇡", dirOpPanelBlock);
    moveDirDownButton = new QPushButton("⇣", dirOpPanelBlock);

    static_cast<QHBoxLayout*>(dirOpPanelBlock->layout())->addWidget(addNewDirButton, 0, Qt::AlignLeft);
    static_cast<QHBoxLayout*>(dirOpPanelBlock->layout())->addWidget(removeDirButton, 0, Qt::AlignLeft);
    static_cast<QHBoxLayout*>(dirOpPanelBlock->layout())->addWidget(moveDirUpButton, 0, Qt::AlignLeft);
    static_cast<QHBoxLayout*>(dirOpPanelBlock->layout())->addWidget(moveDirDownButton, 0, Qt::AlignLeft);
    static_cast<QHBoxLayout*>(dirOpPanelBlock->layout())->addStretch(INT_MAX);

    connect(selectSavePathButton, &QPushButton::clicked, this, [&]() {
        QString selectedPath = QFileDialog::getExistingDirectory(this);
        savePathLabel->setText(selectedPath);
    });

    connect(addNewDirButton, &QPushButton::clicked, this, &MLNKDirListSelectorDialog::addNewDir);
    connect(removeDirButton, &QPushButton::clicked, this, &MLNKDirListSelectorDialog::removeDir);
}

MLNKDirListSelectorDialog::~MLNKDirListSelectorDialog() {
}

void MLNKDirListSelectorDialog::openDirListConfig(MLNKDirListSelectorMode mode) {
    // 读入目录列表
    if (mode == MLNKDirSelectorModeSnapshot) {
        this->dirList = configStore.snapshotDir();
    } else {
        this->dirList.clear();
    }
    // 将目录列表填入表格
    this->refreshDirList();
    this->show();
}

void MLNKDirListSelectorDialog::refreshDirList() {
    dirTableWidget->setRowCount(this->dirList.length());
    for (int i=0; i<this->dirList.length(); i++) {
        QTableWidgetItem *item = dirTableWidget->item(i, 0);
        if (item == nullptr) {
            item = new QTableWidgetItem();
            dirTableWidget->setItem(i, 0, item);
        }
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);
        item->setText(this->dirList.at(i));
    }
}

void MLNKDirListSelectorDialog::addNewDir() {
    QString selectedPath = QFileDialog::getExistingDirectory(this);
    if ((selectedPath != nullptr) && (!selectedPath.isEmpty())) {
        this->dirList.push_back(selectedPath);
        this->saveDirList();
        this->refreshDirList();
    }
}

void MLNKDirListSelectorDialog::removeDir() {
    QList<QTableWidgetItem*> selectedItems = dirTableWidget->selectedItems();
    if (selectedItems.length() > 0) {
        int selectedRow = selectedItems.at(0)->row();
        dirList.removeAt(selectedRow);
        this->saveDirList();
        this->refreshDirList();
    }
}

void MLNKDirListSelectorDialog::saveDirList() {
    if (selectorMode == MLNKDirSelectorModeSnapshot) {
        configStore.setSnapshotDir(this->dirList);
    }
}
