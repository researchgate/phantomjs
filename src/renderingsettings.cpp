#include "renderingsettings.h"

RenderingSettings::RenderingSettings()
{

}

void RenderingSettings::read(const QJsonObject &json) {
    if (json["page"].isObject()) {
        pageSettings.read(json["page"].toObject());
    }
    if (json["printer"].isObject()) {
        printerSettings.read(json["printer"].toObject());
    }
}

PageSettings RenderingSettings::getPageSettings() const {
    return pageSettings;
}

PrinterSettings RenderingSettings::getPrinterSettings() const {
    return printerSettings;
}
