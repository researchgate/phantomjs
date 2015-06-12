#ifndef PDFSETTINGS_H
#define PDFSETTINGS_H

#include <QJsonObject>
#include "pagesettings.h"
#include "printersettings.h"

class RenderingSettings
{
public:
    RenderingSettings();
    void read(const QJsonObject &json);
    PageSettings getPageSettings() const;
    PrinterSettings getPrinterSettings() const;
private:
    PageSettings pageSettings;
    PrinterSettings printerSettings;
};

#endif // PDFSETTINGS_H
