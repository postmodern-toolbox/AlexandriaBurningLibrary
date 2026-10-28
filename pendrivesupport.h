#ifndef PENDRIVESUPPORT_H
#define PENDRIVESUPPORT_H
#include <QStringList>

class PendriveSupport
{
private:
    PendriveSupport();

public:
    static QStringList getAvailablePendrives();
    static bool canPendriveBeInitialized(const QString & path);
    static QString searchPendriveForProject(const QString & projectName);
    static bool initializePendrive(const QString & pathPendrive, const QString & projectName);

};

#endif // PENDRIVESUPPORT_H
