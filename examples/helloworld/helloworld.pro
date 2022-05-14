TEMPLATE = app

DESTDIR = $$PWD
SOURCES += $$PWD/main.cpp
TARGET = helloworld

include($$PWD/config/config.pri)
include($$PWD/../../core.pri)

HEADERS += laptops.h
