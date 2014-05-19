TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
LIBS += -lfreeglut

SOURCES += main.cpp

HEADERS += \
    materiais.hpp

OTHER_FILES += \
    obj_loading_function.pro.user
