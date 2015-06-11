TEMPLATE = app
TARGET = pdfmaker
QT += network webkitwidgets
CONFIG += console

DESTDIR = ../bin

HEADERS += \
    requesthandler.h

SOURCES += main.cpp \
    requesthandler.cpp

include(logging/logging.pri)
include(httpserver/httpserver.pri)

win32: RC_FILE = pdfmaker_win.rc
os2:   RC_FILE = pdfmaker_os2.rc

mac {
    QMAKE_CXXFLAGS += -fvisibility=hidden
    QMAKE_LFLAGS += '-sectcreate __TEXT __info_plist Info.plist'
    CONFIG -= app_bundle
# Uncomment to build a Mac OS X Universal Binary (i.e. x86 + ppc)
#    CONFIG += x86 ppc
}

win32-msvc* {
    LIBS += -lCrypt32 -llibxml2    
    CONFIG(static) {
        DEFINES += STATIC_BUILD
    }
}

openbsd* {
    LIBS += -L/usr/X11R6/lib
}
