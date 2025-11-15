#include "mlnk_infolineparser.h"

MLNKInfoLineParser::MLNKInfoLineParser(QString text): text(text), charpos(0) {
}

QString MLNKInfoLineParser::findNextField(bool *success) {
    QString strCache;
    bool escapedMode = false;
    if (charpos < text.length()) {
        for (; charpos < text.length(); charpos++) {
            QChar ch = text.at(charpos);
            if (ch == '\\') {
                escapedMode = true;
            } else {
                if (escapedMode) {
                    if (ch == 'n') {
                        strCache.append('\n');
                    } else {
                        strCache.append(ch);
                    }
                } else {
                    if (ch == ',') {
                        // 指向下一个字符并返回结果
                        charpos++;
                        *success = true;
                        return strCache;
                    } else {
                        strCache.append(ch);
                    }
                }
            }
        }
        *success = true;
        return strCache;
    } else {
        *success = false;
        return "";
    }

}
