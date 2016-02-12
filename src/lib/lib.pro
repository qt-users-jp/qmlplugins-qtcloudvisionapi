MODULE = cloudvisionapi
TARGET = QtCloudVisionAPI

load(qt_module)

QT = core gui network
CONFIG += c++11
CONFIG-=create_cmake

DEFINES += QTCLOUDVISIONAPI_LIBRARY

HEADERS += \
    qcloudvisionapi_global.h \
    qabstractcloudvisionapi.h \
    qfacedetectionmodel.h \
    qlandmarkdetectionmodel.h \
    qlogodetectionmodel.h \
    qlabeldetectionmodel.h \
    qtextdetectionmodel.h \
    qsafesearchdetectionmodel.h \
    qsuggestiondetectionmodel.h \
    qcloudvisionapisettings.h

SOURCES += \
    qabstractcloudvisionapi.cpp \
    qfacedetectionmodel.cpp \
    qlandmarkdetectionmodel.cpp \
    qlogodetectionmodel.cpp \
    qlabeldetectionmodel.cpp \
    qtextdetectionmodel.cpp \
    qsafesearchdetectionmodel.cpp \
    qsuggestiondetectionmodel.cpp \
    qcloudvisionapisettings.cpp
