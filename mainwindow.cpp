#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "projectconfiguratordialog.h"
#include "configuredialog.h"

#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentProjectDirty(false){
    ui->setupUi(this);
    // TODO updateStatus?

    ui->configButton->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));
    ui->newButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    ui->openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->syncButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    connect(ui->newButton, &QPushButton::clicked, this, &MainWindow::openProjectConfigurationDialog);
    connect(ui->configButton, &QPushButton::clicked, this, &MainWindow::openConfigurationDialog);


    ui->addToProject->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->removeFromProject->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->moveUpInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    ui->moveDownInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

    // dummy values
    for(int i=0; i<30; ++i) {
        ui->projectDirectories->addItem(QString("Example line %1").arg(i));
        ui->databaseDirectories->addItem(QString("Example line aaaa %1").arg(i));

        if(i % 3 == 0) {
            QListWidgetItem *colorRow = ui->projectDirectories->item(i);
            if (colorRow) {
                colorRow->setForeground(QBrush(QColor(0x0000FF)));
            }
        }

    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openProjectConfigurationDialog() {
    ProjectConfiguratorDialog dialog(this);
    int ret = dialog.exec();
    if(ret) {
        // TODO if empty
        ProjectConfig p = dialog.getProjectConfig();
        currentProjectName = p.key;
        currentPendrivePath = p.path;
        currentProjectType = p.type;
        currentProjectDirty = true;
        updateStatus();
    }
}
void MainWindow::openConfigurationDialog() {
    ConfigureDialog dialog(this);
    // todo prefill with current values
    int ret = dialog.exec();
       if(ret) {
           // todo if noempty
           databasePath = dialog.getMusicDir();
           projectsConfigsPath = dialog.getProjectsDir();
       }
}

void MainWindow::saveSettings() {
    // todo connect
    QSettings settings(QCoreApplication::applicationDirPath() + "/AlexandriaBurningLibrary.ini", QSettings::IniFormat);
    settings.setValue("abl/musicDir", databasePath);
    settings.setValue("abl/projectsDir",projectsConfigsPath);
    settings.sync();
}

void MainWindow::readSettings() {
    //todo connect
    QSettings settings(QCoreApplication::applicationDirPath() + "/AlexandriaBurningLibrary.ini", QSettings::IniFormat);
    databasePath = settings.value("abl/musicDir").toString();
    projectsConfigsPath = settings.value("abl/projectsDir").toString();
    qDebug() << "database " << databasePath ;
    qDebug() << "project " << projectsConfigsPath ;

}

void MainWindow::updateStatus() {
    QString status = QString("Project: %1, pendrive: %2, status: %3")
                         .arg(currentProjectName)
                         .arg("OFFLINE")
                         .arg(currentProjectDirty?"CHANGED":"CLEAN");
    ui->projectStatus->setText(status);

}
