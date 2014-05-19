TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
LIBS += -lfreeglut

SOURCES += main.cpp

HEADERS += \
    materiais.hpp

OTHER_FILES += \
    CG_FPS_project.pro.user
