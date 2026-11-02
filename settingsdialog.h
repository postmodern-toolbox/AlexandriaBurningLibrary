#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr);
    ~SettingsDialog();
    QString getMusicDir() const;
    QString getProjectsDir() const;

    void setMusicDir(const QString & text);
    void setProjectsDir(const QString & text);

    void browseMusicDir();
    void browseProjectDir();


private:
    Ui::SettingsDialog *ui;
};

#endif // SETTINGSDIALOG_H
