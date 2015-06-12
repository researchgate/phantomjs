#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H

#include <QtWebKitWidgets>
#include <httpserver/httprequesthandler.h>

class RequestHandler : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY(RequestHandler)
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestHandler(QObject* parent=0);

    /** Destructor */
    virtual ~RequestHandler();

    /**
      Process an incoming HTTP request.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service(HttpRequest& request, HttpResponse& response);
protected:
    QWebPage *m_page;
};

#endif // REQUESTHANDLER_H
