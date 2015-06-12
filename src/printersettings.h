#ifndef PRINTERSETTINGS_H
#define PRINTERSETTINGS_H

#include <QJsonObject>

class PrinterSettings
{
public:
    PrinterSettings();
    void read(const QJsonObject &json);
    qreal getPaperSizeWidth() const;
    qreal getPaperSizeHeight() const;
    QString getPaperSizeUnit() const;
private:
    qreal paperSizeWidth;
    qreal paperSizeHeight;
    QString paperSizeUnit;
};

#endif // PRINTERSETTINGS_H
