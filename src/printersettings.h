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
    QString getPageOrientation() const;
    int getDpi() const;
private:
    qreal paperSizeWidth;
    qreal paperSizeHeight;
    QString paperSizeUnit;
    QString pageOrientation;
    int dpi;
};

#endif // PRINTERSETTINGS_H
