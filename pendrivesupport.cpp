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
        qDebug() << "Root Path:" << storage.rootPath(); // Use this path to read/write files

        if(isPenDrive) {
            list.push_back(root);
        }
    }
    return list;
}

// requirement: pendrive must be empty
// TODO: text files are allowed
bool PendriveSupport::canPendriveBeInitialized(const QString & path) {
    QDir dir(path);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::Dirs);

    bool res = dir.entryList().isEmpty();
    qDebug() << " canPendriveBeInitialized for path: " << path << " : " << res;
    return res;
}

QString PendriveSupport::searchPendriveForProject(const QString &projectName) {
    //QList<QStorageInfo> volumes = QStorageInfo::mountedVolumes();
    qDebug() << "Searching for available pen drives...";
    for (const QString &root : getAvailablePendrives()) {
            QFileInfo checkFile(root+"/"+projectName+".txt");
            if(checkFile.exists() && checkFile.isFile()) {
                qDebug() << "FOUND path: " << root << " for project: " << projectName;
                return root;
        }
    }
    qDebug() << "NOT FOUND path for project: " << projectName;
    return QString();
}

bool PendriveSupport::initializePendrive(const QString &pathPendrive, const QString &projectName) {
    QFile file(pathPendrive+"/"+projectName+".txt");
    // Create empty file
    if (file.open(QIODevice::WriteOnly)) {
        file.close();
        return true;
    } else {
        qWarning() << " Cannot create file: " << pathPendrive+"/"+projectName+".txt";
    }
    return false;
}
