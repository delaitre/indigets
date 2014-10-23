TEMPLATE = app
CONFIG += c++11

QT += qml quick

SOURCES += src/main.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH = ../indigets ./src/qml ../

# Default rules for deployment.
include(deployment.pri)
