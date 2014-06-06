TEMPLATE = app

QT += qml quick
QT += sql
QT += core
SOURCES += main.cpp \
    sqlitedatabase.cpp

RESOURCES += qml.qrc

ios {
    LIBS += -framework UIKit
}

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    sqlitedatabase.h \
    definition.h
