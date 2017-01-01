#-------------------------------------------------
#
# Project created by QtCreator 2017-01-01T02:57:55
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtEx
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../fx2pipe-0.8/usb_io/cycfx2dev.cc \
    ../fx2pipe-0.8/usb_io/fx2usb.cc \
    ../fx2pipe-0.8/usb_io/urbcache.cc \
    ../fx2pipe-0.8/usb_io/wwusb.cc \
    ../fx2pipe-0.8/firmware/fx2pipe_static.cc \
    ../fx2pipe-0.8/fx2pipe/fx2pipe.cc

HEADERS  += mainwindow.h \
    ../fx2pipe-0.8/usb_io/cycfx2dev.h \
    ../fx2pipe-0.8/usb_io/fx2usb.h \
    ../fx2pipe-0.8/usb_io/urbcache.h \
    ../fx2pipe-0.8/usb_io/wwusb.h \
    ../fx2pipe-0.8/lib/linkedlist.h \
    ../fx2pipe-0.8/lib/linearqueue.h \
    ../fx2pipe-0.8/fx2pipe/fx2pipe.h

FORMS    += mainwindow.ui

unix|win32: LIBS += -lusb

DISTFILES += \
    fw.ihx
