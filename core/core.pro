TEMPLATE = lib
CONFIG += qt plugin static
QT += declarative

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += \
    tools.hpp \
    abstractscaleengine.hpp \
    linearscaleengine.hpp \
    stepscaleengine.hpp \
    abstractscale.hpp \
    linearscale.hpp \
    circularscale.hpp \
    fixedscaleengine.hpp \
    ellipse.hpp

SOURCES += \
    tools.cpp \
    abstractscaleengine.cpp \
    linearscaleengine.cpp \
    stepscaleengine.cpp \
    abstractscale.cpp \
    linearscale.cpp \
    circularscale.cpp \
    fixedscaleengine.cpp \
    ellipse.cpp
