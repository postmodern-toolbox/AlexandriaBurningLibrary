#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QDialog>

namespace Ui {
class ConfigureDialog;
}

class ConfigureDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigureDialog(QWidget *parent = nullptr);
    ~ConfigureDialog();
    QString getMusicDir() const;
    QString getProjectsDir() const;

    void setMusicDir(const QString & text);
    void setProjectsDir(const QString & text);

    void browseMusicDir();
    void browseProjectDir();


private:
    Ui::ConfigureDialog *ui;
};

#endif // CONFIGUREDIALOG_H
