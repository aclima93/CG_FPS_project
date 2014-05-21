TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
LIBS += -lfreeglut

SOURCES += main.cpp \
    RgbImage.cpp

HEADERS += \
    materiais.hpp \
    RgbImage.h \
    Camera.hpp \
    Bullet.hpp \
    main.hpp \
    Textures.hpp \
    main.cpp.autosave \
    main.hpp.autosave \
    Map.hpp \
    Map.hpp.autosave \
    Wall.hpp \
    Colors.hpp

OTHER_FILES += \
    CG_FPS_project.pro.user \
    models_textures/textures/grass_tex.bmp \
    models_textures/textures/ground_tex.bmp \
    models_textures/textures/grass_tex.jpg \
    models_textures/textures/ground_tex.jpg \
    NOTA_SOBRE_FICHEIROS.txt
