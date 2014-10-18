TEMPLATE = lib
CONFIG += qt plugin
QT += qml quick svg

TARGET = $$qtLibraryTarget(indigets)

DESTDIR = ../indigets
OBJECTS_DIR = tmp
MOC_DIR = tmp


HEADERS += plugin.hpp \
    abstractscale.hpp \
    circularscale.hpp \
    ellipse.hpp \
    fixedtickengine.hpp \
    linearscale.hpp \
    linearvaluemapper.hpp \
    scalezone.hpp \
    standardscalezone.hpp \
    steptickengine.hpp \
    tickengine.hpp \
    timestamptickengine.hpp \
    tools.hpp \
    valuemapper.hpp
SOURCES += plugin.cpp \
    abstractscale.cpp \
    circularscale.cpp \
    ellipse.cpp \
    fixedtickengine.cpp \
    linearscale.cpp \
    linearvaluemapper.cpp \
    scalezone.cpp \
    standardscalezone.cpp \
    steptickengine.cpp \
    tickengine.cpp \
    timestamptickengine.cpp \
    tools.cpp \
    valuemapper.cpp

OTHER_FILES = \
    ../demo/components/CircularButton.qml \
    ../demo/components/Field.qml \
    ../demo/components/Gauge.qml \
    ../demo/components/Label.qml \
    ../demo/components/Led.qml \
    ../demo/components/Marker.qml \
    ../demo/components/Pointer.qml \
    ../demo/components/Rotator.qml \
    ../demo/components/Scaler.qml \
    ../demo/components/SquareButton.qml \
    ../demo/components/Tank.qml \
    ../demo/examples/demo1.qml \
    qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target

    copy_qmlcomponents.target = $$OUT_PWD/qmlcomponents
    copy_qmlcomponents.depends = $$_PRO_FILE_PWD_/../demo/components/*.qml
    copy_qmlcomponents.commands = $(COPY) $$replace(copy_qmlcomponents.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_qmlcomponents
    PRE_TARGETDEPS += $$copy_qmlcomponents.target

    copy_qmlexamples.target = $$OUT_PWD/qmlexamples
    copy_qmlexamples.depends = $$_PRO_FILE_PWD_/../demo/examples/*.qml
    copy_qmlexamples.commands = $(COPY) $$replace(copy_qmlexamples.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_qmlexamples
    PRE_TARGETDEPS += $$copy_qmlexamples.target

    copy_resources.target = $$OUT_PWD/resources
    copy_resources.depends = $$_PRO_FILE_PWD_/../demo/resources/*.svg
    copy_resources.commands = $(COPY) $$replace(copy_resources.depends, /, $$QMAKE_DIR_SEP) .
    QMAKE_EXTRA_TARGETS += copy_resources
    PRE_TARGETDEPS += $$copy_resources.target
}

qmldir.files = qmldir
qmlcomponents.files = ../demo/components/*.qml
qmlexamples.files = ../demo/examples/*.qml
resources.files = ../demo/resources/*.svg
