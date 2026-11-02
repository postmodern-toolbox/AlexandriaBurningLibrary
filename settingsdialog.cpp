#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>

SettingsDialog::SettingsDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);

    connect(ui->musicBaseDirBrowseButton, &QPushButton::clicked, this, &SettingsDialog::browseMusicDir);
    connect(ui->projectDirBaseBrowseButton, &QPushButton::clicked, this, &SettingsDialog::browseProjectDir);

}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

QString SettingsDialog::getMusicDir() const {
    return ui->musicBaseDirEdit->text();
}

QString SettingsDialog::getProjectsDir() const {
    return ui->projectDirBaseEdit->text();
}
void SettingsDialog::setMusicDir(const QString & text) {
    ui->musicBaseDirEdit->setText(text);
}

void SettingsDialog::setProjectsDir(const QString & text) {
    ui->projectDirBaseEdit->setText(text);
}

void SettingsDialog::browseMusicDir() {
    qDebug() << "browse MusicDir";

    QString musicDir = QFileDialog::getExistingDirectory(this, "Browse music dir",getMusicDir(),QFileDialog::ShowDirsOnly);
    if(musicDir.isEmpty()){
        return;
    }
    qDebug() << musicDir;
    ui->musicBaseDirEdit->setText(musicDir);
}

void SettingsDialog::browseProjectDir() {
    qDebug() << " browse ProjectDir";
    QString projectDir = QFileDialog::getExistingDirectory(this, "Browse project dir",getProjectsDir(),QFileDialog::ShowDirsOnly);
    if(projectDir.isEmpty()){
        return;
    }
    qDebug() << projectDir;
    ui->projectDirBaseEdit->setText(projectDir);
}
