TEMPLATE = lib
CONFIG += qt plugin static
QT += declarative

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += \
    tools.hpp \
    steptickengine.hpp \
    abstractscale.hpp \
    linearscale.hpp \
    circularscale.hpp \
    fixedtickengine.hpp \
    ellipse.hpp \
    scalezone.hpp \
    valuemapper.hpp \
    tickengine.hpp \
    linearvaluemapper.hpp \
    standardscalezone.hpp

SOURCES += \
    tools.cpp \
    steptickengine.cpp \
    abstractscale.cpp \
    linearscale.cpp \
    circularscale.cpp \
    fixedtickengine.cpp \
    ellipse.cpp \
    scalezone.cpp \
    valuemapper.cpp \
    tickengine.cpp \
    linearvaluemapper.cpp \
    standardscalezone.cpp
