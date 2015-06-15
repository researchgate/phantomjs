#include <logging/filelogger.h>
#include "requesthandler.h"
#include <QJsonDocument>
#include "renderingsettings.h">

/** Logger class */
extern FileLogger* logger;

RequestHandler::RequestHandler(QObject* parent)
    :HttpRequestHandler(parent) {
    m_page = NULL;
}

RequestHandler::~RequestHandler() {
    if (m_page != NULL) {
        delete m_page;
        m_page = NULL;
    }
}

void RequestHandler::service(HttpRequest& request, HttpResponse& response) {
    if (request.getMethod().toUpper() != "POST") {
        qDebug("Endpoint was called with method [%s]", request.getMethod().toUpper().data());
        response.setStatus(405, "Only Post request supported");
        logger->clear();
        return;
    }
    if (request.getHeader("Content-Type") != "application/json") {
        qDebug("Endpoint was called with Content-Type [%s]", request.getHeader("Content-Type").data());
        response.setStatus(406, "Only requests with Content-Type application/json are supported");
        logger->clear();
        return;
    }
    QByteArray body = request.getBody();
    QByteArray path = request.getPath();
    qDebug("Conroller: path=%s",path.data());


    RenderingSettings pdfSettings;
    QJsonDocument json = QJsonDocument::fromJson(body);
    if (!json.isObject()) {
        qDebug("Body was not in valid json format");
        response.setStatus(405, "The body must contain valid json.");
        logger->clear();
        return;
    }

    pdfSettings.read(json.object());
    if (m_page == NULL) {
        m_page = new QWebPage();
    }
    QSize viewportSize(pdfSettings.getPageSettings().getViewportWidth(), pdfSettings.getPageSettings().getViewportHeight());
    m_page->setViewportSize(viewportSize);

    QEventLoop loop;
    loop.connect(m_page, SIGNAL(loadFinished(bool)), SLOT(quit()), Qt::QueuedConnection);
    m_page->mainFrame()->setHtml(pdfSettings.getPageSettings().getHtml());
    loop.exec();

    QPrinter printer(QPrinter::HighResolution);
    QString filename = "/tmp/" + QUuid::createUuid().toString() + ".pdf";
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filename);
    printer.setResolution(pdfSettings.getPrinterSettings().getDpi());
    QPageLayout::Orientation pageOrientation = pdfSettings.getPrinterSettings().getPageOrientation() == "landscape" ? QPageLayout::Landscape : QPageLayout::Portrait;
    printer.setPageOrientation(pageOrientation);

    static const struct {
                QString format;
                QPrinter::Unit unit;
            } units[] = {
                { "mm", QPrinter::Millimeter },
                { "pt", QPrinter::Point },
                { "in", QPrinter::Inch },
                { "px", QPrinter::DevicePixel }
            };

    printer.setPaperSize(QPrinter::A4);
    const QSizeF sizePt(pdfSettings.getPrinterSettings().getPaperSizeWidth(),
                        pdfSettings.getPrinterSettings().getPaperSizeHeight());
    QPrinter::Unit unit = QPrinter::Point;
    for (uint i = 0; i < sizeof(units) / sizeof(units[0]); ++i) {
        if (pdfSettings.getPrinterSettings().getPaperSizeUnit().compare(units[i].format, Qt::CaseInsensitive) == 0) {
            unit = units[i].unit;
            break;
        }
    }
    printer.setPaperSize(sizePt, unit);
    m_page->mainFrame()->print(&printer);
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
    delete m_page;
    m_page = NULL;
}
