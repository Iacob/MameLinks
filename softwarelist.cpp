#include "softwarelist.h"

#include <iostream>
#include <QFile>
#include <QtXml>

#include "mlnk_infolineparser.h"

SoftwareList::SoftwareList() {}

void SoftwareList::readSoftwareList(SoftwareInfo* softwareInfos, int* softwareCount) {
    QFile softwareListFile = QFile(":/res/mame0280.txt");
    softwareListFile.open(QFile::ReadOnly);

    int lineNum = 0;
    QByteArray lineBytes = softwareListFile.readLine();
    do {
        QString lineStr = QString::fromUtf8(lineBytes);
        MLNKInfoLineParser lineParser(lineStr);
        bool ifSuccess = false;
        QString name = lineParser.findNextField(&ifSuccess);
        QString description = lineParser.findNextField(&ifSuccess);
        QString manufacturer = lineParser.findNextField(&ifSuccess);
        QString year = lineParser.findNextField(&ifSuccess);
        softwareInfos[lineNum].name = name.trimmed();
        softwareInfos[lineNum].description = description.trimmed();
        softwareInfos[lineNum].manufacturer = manufacturer.trimmed();
        softwareInfos[lineNum].year = year.trimmed();

        // std::cout << "name: " << qPrintable(name) << std::endl;
        // std::cout << "description: " << qPrintable(description) << std::endl;
        // std::cout << "manufacturer: " << qPrintable(manufacturer) << std::endl;
        // std::cout << "year: " << qPrintable(year) << std::endl;
        // std::cout << "-----" << std::endl;

        lineBytes = softwareListFile.readLine();
        lineNum++;
    } while (lineBytes.length() > 0);


    *softwareCount = lineNum;

    // QByteArray fileContent = softwareListFile.readAll();
    // QString fileContentStr = QString::fromUtf8(fileContent);
    // softwareListFile.close();

    // QDomDocument xmlDoc;
    // xmlDoc.setContent(fileContentStr);
    // QDomNodeList nodeList = xmlDoc.elementsByTagName("machine");
    // std::cout << "machine count: " << nodeList.count() << std::endl;

    // *softwareCount = nodeList.count();

    // for (int i=0; i<nodeList.count(); i++) {
    //     QDomNode node1 = nodeList.at(i);
    //     QDomNamedNodeMap attrMap = node1.attributes();
    //     QDomNode attrName = attrMap.namedItem("name");
    //     //std::cout << qPrintable(attrName.nodeValue()) << std::endl;

    //     softwareInfos[i].name = attrName.nodeValue();

    //     QDomNodeList node1DetailNodes = node1.childNodes();
    //     for (int j=0; j<node1DetailNodes.count(); j++) {
    //         QDomNode detailNode1 = node1DetailNodes.at(j);
    //         if (detailNode1.nodeName() == "description") {
    //             softwareInfos[i].description = detailNode1.firstChild().toText().data();
    //         }
    //         if (detailNode1.nodeName() == "manufacturer") {
    //             softwareInfos[i].manufacturer = detailNode1.firstChild().toText().data();
    //         }
    //         if (detailNode1.nodeName() == "year") {
    //             softwareInfos[i].year = detailNode1.firstChild().toText().data();
    //         }
    //         // std::cout << "  " << qPrintable(node1DetailNodes.at(j).nodeName()) << "  value: " << qPrintable(node1DetailNodes.at(j).firstChild().toText().data()) << std::endl;
    //         // QDomNode textNode = node1DetailNode.at(i).firstChild();
    //         // std::cout << qPrintable(textNode.toText().data()) << std::endl;
    //     }
    // }
}

QString SoftwareList::unescapeText(QString text) {
    QString resultStr = "";
    bool unescapeMode = false;
    for (QChar ch : text) {
        if (ch == '\\') {
            unescapeMode = true;
        } else {
            if (unescapeMode) {
                if (ch == 'n') {
                    resultStr.append('\n');
                } else {
                    resultStr.append(ch);
                }
                unescapeMode = false;
            } else {
                resultStr.append(ch);
            }
        }
    }
    return resultStr;
}
