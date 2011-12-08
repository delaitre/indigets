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
    components/Rotator.qml \
    components/Gauge.qml \
    components/Scaler.qml

OTHER_FILES = \
    $$QML_FILES \
    qmldir \
    examples/demo1.qml \
    examples/ValueChanger.qml \
    components/Tank.qml \
    components/Marker.qml \
    components/Pointer.qml

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target

    copy_qmlcomponents.target = $$OUT_PWD/qmlcomponents
    copy_qmlcomponents.depends = $$_PRO_FILE_PWD_/components/*.qml
    copy_qmlcomponents.commands = $(COPY) $$replace(copy_qmlcomponents.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_qmlcomponents
    PRE_TARGETDEPS += $$copy_qmlcomponents.target

    copy_qmlexamples.target = $$OUT_PWD/qmlexamples
    copy_qmlexamples.depends = $$_PRO_FILE_PWD_/examples/*.qml
    copy_qmlexamples.commands = $(COPY) $$replace(copy_qmlexamples.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_qmlexamples
    PRE_TARGETDEPS += $$copy_qmlexamples.target

    copy_resources.target = $$OUT_PWD/resources
    copy_resources.depends = $$_PRO_FILE_PWD_/resources/*.svg
    copy_resources.commands = $(COPY) $$replace(copy_resources.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_resources
    PRE_TARGETDEPS += $$copy_resources.target
}

qmldir.files = qmldir
qmlcomponents.files = components/*.qml
qmlexamples.files = examples/*.qml
resources.files = resources/*.svg
