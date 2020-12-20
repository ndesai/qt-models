TEMPLATE = lib
TARGET = ModelsPlugin
QT += qml quick sql core
CONFIG += qt plugin

TARGET = $$qtLibraryTarget($$TARGET)
uri = st.app.models

ios {
static: QMAKE_MOC_OPTIONS += -Muri=st.app.models
CONFIG += static
}

# Input
SOURCES += \
    models_plugin.cpp \
    myitem.cpp \
    sqlitedatabase.cpp

HEADERS += \
    models_plugin.h \
    myitem.h \
    sqlitedatabase.h \
    definition.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}
osx {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

