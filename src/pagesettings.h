#ifndef PAGESETTINGS_H
#define PAGESETTINGS_H

#include <QJsonObject>

class PageSettings
{
public:
    PageSettings();
    void read(const QJsonObject &json);
    int getViewportWidth() const;
    int getViewportHeight() const;
    QString getHtml() const;
private:
    int viewportWidth;
    int viewportHeight;
    QString html;
};

#endif // PAGESETTINGS_H
