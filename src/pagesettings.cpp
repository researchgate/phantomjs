#include "pagesettings.h"

PageSettings::PageSettings()
{

}

void PageSettings::read(const QJsonObject &json) {
    viewportWidth = json["viewportWidth"].toInt();
    viewportHeight = json["viewportHeight"].toInt();
    html = json["html"].toString();
}

int PageSettings::getViewportWidth() const {
    return viewportWidth;
}

int PageSettings::getViewportHeight() const {
    return viewportHeight;
}

QString PageSettings::getHtml() const {
    return html;
}
