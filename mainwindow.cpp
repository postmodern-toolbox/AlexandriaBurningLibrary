#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "projectconfiguratordialog.h"
#include "configuredialog.h"

#include <QSettings>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , currentProjectDirty(false)
    , pendriveOnline(false)
{
    ui->setupUi(this);

    ui->configButton->setIcon(style()->standardIcon(QStyle::SP_DialogHelpButton));
    ui->newButton->setIcon(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    ui->openButton->setIcon(style()->standardIcon(QStyle::SP_DialogOpenButton));
    ui->saveButton->setIcon(style()->standardIcon(QStyle::SP_DialogSaveButton));
    ui->syncButton->setIcon(style()->standardIcon(QStyle::SP_BrowserReload));

    connect(ui->newButton, &QPushButton::clicked, this, &MainWindow::openProjectConfigurationDialog);
    connect(ui->configButton, &QPushButton::clicked, this, &MainWindow::openConfigurationDialog);
    connect(ui->saveButton, &QPushButton::clicked, this, &MainWindow::saveProject);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::loadProject);
    connect(ui->syncButton, &QPushButton::clicked, this, &MainWindow::syncToPendrive);


    ui->addToProject->setIcon(style()->standardIcon(QStyle::SP_ArrowLeft));
    ui->removeFromProject->setIcon(style()->standardIcon(QStyle::SP_ArrowRight));
    ui->moveUpInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    ui->moveDownInProject->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));

    readSettings();
    loadDatabase();
    //loadProject();
    updateStatus();

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
    dialog.setMusicDir(databasePath);
    dialog.setProjectsDir(projectsConfigsPath);
    int ret = dialog.exec();
    if(ret) {
        // todo if noempty
        databasePath = dialog.getMusicDir();
        projectsConfigsPath = dialog.getProjectsDir();
        //saveSettings();
    }
}

void MainWindow::saveSettings() {
    QSettings settings(QCoreApplication::applicationDirPath() + "/AlexandriaBurningLibrary.ini", QSettings::IniFormat);
    settings.setValue("abl/musicDir", databasePath);
    settings.setValue("abl/projectsDir", projectsConfigsPath);
    settings.sync();
    qDebug() << "save database " << databasePath ;
    qDebug() << "save projectPath " << projectsConfigsPath ;
}

void MainWindow::saveProject() {
    qDebug() << "save project " << currentProjectName ;
    currentProjectDirty=false;
    // TODO logic

    updateStatus();
}

void MainWindow::readSettings() {
    QSettings settings(QCoreApplication::applicationDirPath() + "/AlexandriaBurningLibrary.ini", QSettings::IniFormat);
    databasePath = settings.value("abl/musicDir").toString();
    projectsConfigsPath = settings.value("abl/projectsDir").toString();
    qDebug() << "database " << databasePath ;
    qDebug() << "project " << projectsConfigsPath ;

}

void MainWindow::updateStatus() {
    QString status = QString("Project: %1, pendrive: %2, status: %3")
                         .arg(currentProjectName.isEmpty()?"<none>":currentProjectName)
                         .arg(pendriveOnline?"ONLINE":"OFFLINE")
                         .arg(currentProjectDirty?"CHANGED":"CLEAN");
    ui->projectStatus->setText(status);

}

void MainWindow::loadDatabase() {
    // TODO dummy values
    ui->databaseDirectories->clear();
    for(int i=0; i<30; ++i) {
        ui->databaseDirectories->addItem(QString("Example line aaaa %1").arg(i));
    }
}

void MainWindow::loadProject() {
    // TODO dummy values
    currentProjectName="DUMMY";
    currentProjectType="FLAT";
    currentProjectDirty=false;

    ui->projectDirectories->clear();
    // TODO actual load
    for(int i=0; i<30; ++i) {
        ui->projectDirectories->addItem(QString("Example line %1").arg(i));
        if(i % 3 == 0) {
            QListWidgetItem *colorRow = ui->projectDirectories->item(i);
            if (colorRow) {
                colorRow->setForeground(QBrush(QColor(0x0000FF)));
            }
        }
    }
}

void MainWindow::syncToPendrive() {
    qDebug() << "syncToPendrive " ;
    if(!pendriveOnline) {
        qDebug() << "syncToPendrive fail: Pendrive OFFLINE" ;
        return;
    }
    if(currentProjectDirty) {
        qDebug() << "syncToPendrive fail: Project not saved" ;
        return;
    }
    // TODO futher
}
