QT += cloudvisionapi quick
CONFIG += c++11

TARGETPATH = jp/qtusers/tasuku/cloudvisionapi

HEADERS +=

SOURCES += main.cpp

load(qml_plugin)

OTHER_FILES = plugins.qmltypes qmldir
