TEMPLATE = app
CONFIG += c++11

QT += qml quick

SOURCES += src/main.cpp

CONFIG(debug, debug|release) {
TARGET = demo_guid
OBJECTS_DIR = build/debug
MOC_DIR     = build/debug
}
else {
TARGET = demo_gui
OBJECTS_DIR = build/release
MOC_DIR     = build/release
}

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../indigets ./src/qml ../

# Default rules for deployment.
include(deployment.pri)
