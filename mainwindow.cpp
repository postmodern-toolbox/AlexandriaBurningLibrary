#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    for(int i=0; i<30; ++i) {
        ui->projectDirectories->addItem(QString("Example line %1").arg(i));

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
