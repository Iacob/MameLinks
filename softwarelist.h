#ifndef SOFTWARELIST_H
#define SOFTWARELIST_H

#include <QString>

struct SoftwareInfo {
    QString name;
    QString description;
    QString year;
    QString manufacturer;
};

class SoftwareList
{
public:
    SoftwareList();
    static void readSoftwareList(SoftwareInfo* softwareInfos, int* softwareCount);
    static QString unescapeText(QString text);
};

#endif // SOFTWARELIST_H
