#include "pendrivesupport.h"
#include <QStorageInfo>

PendriveSupport::PendriveSupport() {}
namespace {

#if defined(Q_OS_WIN)
bool isPathPendrive(QString s){
    if(!s.contains("C:/")){
        return true;
    }
    return false;
}
#endif
//TODO LINUX
}
QStringList PendriveSupport::getAvailablePendrives() {
    QStringList list;
    list.push_back("C:\\ABLTest\\PENDRIVE_A"); // hardocded path for testing

    QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();
    qDebug() << "Searching for available pen drives...";
    for (const QStorageInfo &storage : volumes) {
        bool isPenDrive = false;
        QString root = storage.rootPath();
        if (isPathPendrive(root) && storage.fileSystemType() == "FAT32") {
            isPenDrive = true;
        }
        qDebug() << "-----------------------------------------";
        qDebug() << "isPendrive: " <<   isPenDrive;
        qDebug() << "Name:" << storage.name();
        qDebug() << "Display Name:" << storage.displayName();
        qDebug() << "Root Path:" << storage.rootPath(); // Use this path to read/write files
        qDebug() << "File System:" << storage.fileSystemType();

        if(isPenDrive) {
            list.push_back(root);
        }
    }
    return list;
}

bool PendriveSupport::canPendriveBeInitialized(const QString & path) {
// TODO
    qDebug() << "canPendriveBeInitialized hardcode: " << false;
    return false;
}

QString PendriveSupport::searchPendriveForProject(const QString &projectName) {
    //TODO
    return QString();
}

bool PendriveSupport::initializePendrive(const QString &pathPendrive, const QString &projectName) {

    // TODO
    return false;
}
