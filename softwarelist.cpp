#include "softwarelist.h"

#include <iostream>
#include <QFile>
#include <QtXml>

SoftwareList::SoftwareList() {}

void SoftwareList::readSoftwareList(SoftwareInfo* softwareInfos, int* softwareCount) {
    QFile softwareListFile = QFile(":/res/mame0280.xml");
    softwareListFile.open(QFile::ReadOnly);
    QByteArray fileContent = softwareListFile.readAll();
    QString fileContentStr = QString::fromUtf8(fileContent);
    softwareListFile.close();

    QDomDocument xmlDoc;
    xmlDoc.setContent(fileContentStr);
    QDomNodeList nodeList = xmlDoc.elementsByTagName("machine");
    std::cout << "machine count: " << nodeList.count() << std::endl;

    *softwareCount = nodeList.count();

    for (int i=0; i<nodeList.count(); i++) {
        QDomNode node1 = nodeList.at(i);
        QDomNamedNodeMap attrMap = node1.attributes();
        QDomNode attrName = attrMap.namedItem("name");
        //std::cout << qPrintable(attrName.nodeValue()) << std::endl;

        softwareInfos[i].name = attrName.nodeValue();

        QDomNodeList node1DetailNodes = node1.childNodes();
        for (int j=0; j<node1DetailNodes.count(); j++) {
            QDomNode detailNode1 = node1DetailNodes.at(j);
            if (detailNode1.nodeName() == "description") {
                softwareInfos[i].description = detailNode1.firstChild().toText().data();
            }
            if (detailNode1.nodeName() == "manufacturer") {
                softwareInfos[i].manufacturer = detailNode1.firstChild().toText().data();
            }
            if (detailNode1.nodeName() == "year") {
                softwareInfos[i].year = detailNode1.firstChild().toText().data();
            }
            // std::cout << "  " << qPrintable(node1DetailNodes.at(j).nodeName()) << "  value: " << qPrintable(node1DetailNodes.at(j).firstChild().toText().data()) << std::endl;
            // QDomNode textNode = node1DetailNode.at(i).firstChild();
            // std::cout << qPrintable(textNode.toText().data()) << std::endl;
        }
    }



    // QDomNodeList node1DetailNode = node1.childNodes();
    // for (int i=0; i<node1DetailNode.count(); i++) {
    //     std::cout << "  " << qPrintable(node1DetailNode.at(i).nodeName()) << "  value: " << qPrintable(node1DetailNode.at(i).firstChild().toText().data()) << std::endl;
    //     // QDomNode textNode = node1DetailNode.at(i).firstChild();
    //     // std::cout << qPrintable(textNode.toText().data()) << std::endl;
    // }



    std::cout << "a\n" << std::endl;
}
