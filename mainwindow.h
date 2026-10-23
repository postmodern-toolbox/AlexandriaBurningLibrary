#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void openProjectConfigurationDialog();
    void openConfigurationDialog();

    void updateStatus();

    void saveSettings();
    void readSettings();

private:
    Ui::MainWindow *ui;

    QString databasePath;
    QString projectsConfigsPath;


    QString currentProjectName;
    bool currentProjectDirty;
    QString currentPendrivePath;
    QString currentProjectType;



};
#endif // MAINWINDOW_H
