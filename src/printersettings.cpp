#include "printersettings.h"

PrinterSettings::PrinterSettings()
{

}

void PrinterSettings::read(const QJsonObject &json) {
    paperSizeWidth = json["paperSizeWidth"].toDouble();
    paperSizeHeight = json["paperSizeHeight"].toDouble();
    paperSizeUnit = json["paperSizeUnit"].toString();
}

qreal PrinterSettings::getPaperSizeWidth() const {
    return paperSizeWidth;
}

qreal PrinterSettings::getPaperSizeHeight() const {
    return paperSizeHeight;
}

QString PrinterSettings::getPaperSizeUnit() const {
    return paperSizeUnit;
}
