#ifndef SOFTWAREFILELOCATOR_H
#define SOFTWAREFILELOCATOR_H

#include <QFile>

/**
 * 文件定位工具类
 * @brief The SoftwareFileLocator class
 */
class SoftwareFileLocator
{
public:
    enum FileType {
        FileTypeSnapShot,
        FileTypeCabinet,
        FileTypeFlyer
    };
    SoftwareFileLocator();
    static QString findSnapshotFilePath(FileType fileType, QString software);
};

#endif // SOFTWAREFILELOCATOR_H
