#ifndef PROJECTCONFIG_H
#define PROJECTCONFIG_H
#include <qstring.h>

class ProjectConfig
{
public:
    enum class ConfigType {
        Simple,
        Full,
        Flat
    };

    QString key;
    QString path;
    QString type;


QString toString(ConfigType type);
ConfigType fromString(const QString &str);
};

#endif // PROJECTCONFIG_H
