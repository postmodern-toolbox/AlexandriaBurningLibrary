#include "projectconfig.h"

QString ProjectConfig::toString(ProjectConfig::ConfigType type) {
    switch (type) {
    case ConfigType::Simple:
        return QStringLiteral("Simple");
    case ConfigType::Full:
        return QStringLiteral("Full");
    case ConfigType::Flat:
        return QStringLiteral("Flat");
    }
    return QStringLiteral("Unknown");
}

ProjectConfig::ConfigType ProjectConfig::fromString(const QString &str) {
    if (str.compare(QStringLiteral("Simple"), Qt::CaseInsensitive) == 0) {
        return ConfigType::Simple;
    }
    if (str.compare(QStringLiteral("Full"), Qt::CaseInsensitive) == 0) {
        return ConfigType::Full;
    }
    if (str.compare(QStringLiteral("Flat"), Qt::CaseInsensitive) == 0) {
        return ConfigType::Flat;
    }
    return ConfigType::Simple;
}
