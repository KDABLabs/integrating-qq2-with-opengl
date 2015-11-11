TEMPLATE = lib
CONFIG += static
TARGET = renderlib

SOURCES += \
    objloader.cpp \
    axisalignedboundingbox.cpp \
    camera.cpp \
    meshrenderer.cpp


HEADERS += \
    objloader.h \
    axisalignedboundingbox.h \
    camera.h \
    meshrenderer.h

DISTFILES += \
    lib.pri

RESOURCES += \
    assets.qrc
