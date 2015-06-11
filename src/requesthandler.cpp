#include <logging/filelogger.h>
#include <QtWebKitWidgets>
#include "requesthandler.h"

/** Logger class */
extern FileLogger* logger;

RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent) {}

void RequestHandler::service(HttpRequest& request, HttpResponse& response) {
    if (request.getMethod().toUpper() != "POST") {
        qDebug("Endpoint was called with method [" + request.getMethod().toUpper() + "]");
        response.setStatus(405, "Only Post request supported");
        logger->clear();
        return;
    }
    QByteArray body = request.getBody();
    QByteArray path = request.getPath();
    qDebug("Conroller: path=%s",path.data());

    QWebPage page;
    QSize viewportSize(640, 480);
    page.setViewportSize(viewportSize);
    page.mainFrame()->setHtml(body);

    QPrinter printer(QPrinter::HighResolution);
    QString filename = "/tmp/" + QUuid::createUuid().toString() + ".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setResolution(72);
    printer.setPageOrientation(QPageLayout::Portrait);
    printer.setPaperSize(QPrinter::A4);
    const QSize pageSize = page.mainFrame()->contentsSize();
    const QSizeF sizePt(595.4069,
                        842.0754);
    printer.setPaperSize(sizePt, QPrinter::Point);
    page.mainFrame()->print(&printer);
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly)) {
        response.setStatus(404, "Could not open temporary pdf file");
        return;
    }

    QByteArray pdfData = file.readAll();
    file.remove();

    // Set a response header
    response.setHeader("Content-Type", "application/pdf");
    response.setHeader("Content-Length", pdfData.size());

    // Return a simple HTML document
    response.write(pdfData,true);
    qDebug("Conroller: finished request");
    logger->clear();
}

qreal RequestHandler::stringToPointSize(const QString &string) const
{
    static const struct {
        QString unit;
        qreal factor;
    } units[] = {
        { "mm", 72 / 25.4 },
        { "cm", 72 / 2.54 },
        { "in", 72 },
        { "px", 72.0 / 72.0 },
        { "", 72.0 / 72.0 }
    };
    for (uint i = 0; i < sizeof(units) / sizeof(units[0]); ++i) {
        if (string.endsWith(units[i].unit)) {
            QString value = string;
            value.chop(units[i].unit.length());
            return value.toDouble() * units[i].factor;
        }
    }
    return 0;
}
