TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
LIBS += -lfreeglut

SOURCES += main.cpp \
    RgbImage.cpp

HEADERS += \
    materiais.hpp \
    RgbImage.h

OTHER_FILES += \
    CG_FPS_project.pro.user \
    models_textures/textures/grass_tex.bmp \
    models_textures/textures/ground_tex.bmp \
    models_textures/textures/grass_tex.jpg \
    models_textures/textures/ground_tex.jpg
