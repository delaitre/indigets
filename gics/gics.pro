TEMPLATE = lib
CONFIG += qt plugin
QT += declarative svg

TARGET = $$qtLibraryTarget($$TARGET)

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

INCLUDEPATH += ../core
LIBS += -L../core/lib -lcore

HEADERS += plugin.hpp
SOURCES += plugin.cpp

QML_FILES = \
    components/Label.qml \
    components/Field.qml \
    components/Led.qml \
    components/SquareButton.qml \
    components/CircularButton.qml \
    components/Gauge.qml \
    components/Tank.qml

OTHER_FILES = \
    $$QML_FILES \
    qmldir \
    examples/demo1.qml
