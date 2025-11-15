#ifndef MLNK_INFOLINEPARSER_H
#define MLNK_INFOLINEPARSER_H

#include <QString>

class MLNKInfoLineParser
{
public:
    MLNKInfoLineParser(QString text);
    QString findNextField(bool *success);
private:
    QString text;
    int charpos;
};

#endif // MLNK_INFOLINEPARSER_H
