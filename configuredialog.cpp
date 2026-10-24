#include "configuredialog.h"
#include "ui_configuredialog.h"

#include <QFileDialog>

ConfigureDialog::ConfigureDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ConfigureDialog)
{
    ui->setupUi(this);

    connect(ui->musicBaseDirBrowseButton, &QPushButton::clicked, this, &ConfigureDialog::browseMusicDir);
    connect(ui->projectDirBaseBrowseButton, &QPushButton::clicked, this, &ConfigureDialog::browseProjectDir);

}

ConfigureDialog::~ConfigureDialog()
{
    delete ui;
}

QString ConfigureDialog::getMusicDir() const {
    return ui->musicBaseDirEdit->text();
}

QString ConfigureDialog::getProjectsDir() const {
    return ui->projectDirBaseEdit->text();
}
void ConfigureDialog::setMusicDir(const QString & text) {
    ui->musicBaseDirEdit->setText(text);
}

void ConfigureDialog::setProjectsDir(const QString & text) {
    ui->projectDirBaseEdit->setText(text);
}

void ConfigureDialog::browseMusicDir() {
    qDebug() << "browse MusicDir";

    QString musicDir = QFileDialog::getExistingDirectory(this, "Browse music dir",getMusicDir(),QFileDialog::ShowDirsOnly);
    if(musicDir.isEmpty()){
        return;
    }
    qDebug() << musicDir;
    ui->musicBaseDirEdit->setText(musicDir);
}

void ConfigureDialog::browseProjectDir() {
    qDebug() << " browse ProjectDir";
    QString projectDir = QFileDialog::getExistingDirectory(this, "Browse project dir",getProjectsDir(),QFileDialog::ShowDirsOnly);
    if(projectDir.isEmpty()){
        return;
    }
    qDebug() << projectDir;
    ui->projectDirBaseEdit->setText(projectDir);
}
