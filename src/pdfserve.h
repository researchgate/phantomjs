#ifndef PDFSERVE_H
#define PDFSERVE_H

#include <QObject>

class pdfserve : public QObject
{
    Q_OBJECT
public:
    explicit pdfserve(QObject *parent = 0);

signals:

public slots:
};

#endif // PDFSERVE_H
