#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    ui->newButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    ui->openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->syncButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    ui->addToProject->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->removeFromProject->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->moveUpInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    ui->moveDownInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

    for(int i=0; i<30; ++i) {
        ui->projectDirectories->addItem(QString("Example line %1").arg(i));
        ui->databaseDirectories->addItem(QString("Example line aaaa %1").arg(i));

        if(i % 3 == 0) {
            QListWidgetItem *colorRow = ui->projectDirectories->item(i);
            if (colorRow) {
                colorRow->setForeground(QBrush(QColor("#0000FF")));
            }
        }

    }
}

MainWindow::~MainWindow() {
    delete ui;
}

