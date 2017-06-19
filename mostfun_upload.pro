QT += core network gui widgets

CONFIG += c++11

TARGET = mostfun_upload
#CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    upload_file.cpp \
    upload_window.cpp \
    zero_conf_detector.cpp \
    remote_ctl.cpp \
    panel_controller.cpp \
    printer_info.cpp

TRANSLATIONS = en_CN.ts zh_CN.ts

include(./qtzeroconf.pri)

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    upload_file.h \
    upload_window.h \
    zero_conf_detector.h \
    remote_ctl.h \
    panel_controller.h \
    printer_info.h \
    error_number.h

FORMS += \
    upload_window.ui

RESOURCES += \
    mostfun-src.qrc
