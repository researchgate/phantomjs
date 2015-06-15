#include "printersettings.h"

PrinterSettings::PrinterSettings()
{
    // we chose DIN A4 as default
    paperSizeWidth = 210;
    paperSizeHeight = 297;
    paperSizeUnit = "mm";
    pageOrientation = "portrait";
    dpi = 72;
}

void PrinterSettings::read(const QJsonObject &json) {
    if (json["paperSizeWidth"].isDouble()) {
        paperSizeWidth = json["paperSizeWidth"].toDouble();
    }
    if (json["paperSizeHeight"].isDouble()) {
        paperSizeHeight = json["paperSizeHeight"].toDouble();
    }
    if (json["paperSizeUnit"].isString()) {
        paperSizeUnit = json["paperSizeUnit"].toString();
    }
    if (json["pageOrientation"].isString()) {
        pageOrientation = json["pageOrientation"].toString();
    }
    if (!json["dpi"].isUndefined()) {
        dpi = json["dpi"].toInt();
    }
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

QString PrinterSettings::getPageOrientation() const {
    return pageOrientation;
}

int PrinterSettings::getDpi() const {
    return dpi;
}
