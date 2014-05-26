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
    Colors.hpp \
    BoundingBox.hpp \
    Target.hpp \
    HUD.hpp \
    Sound.hpp

OTHER_FILES += \
    CG_FPS_project.pro.user \
    models_textures/textures/grass_tex.bmp \
    models_textures/textures/ground_tex.bmp \
    models_textures/textures/grass_tex.jpg \
    models_textures/textures/ground_tex.jpg \
    NOTA_SOBRE_FICHEIROS.txt

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/fmod/lib/ -lfmod_vc
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/fmod/lib/ -lfmod_vcd
else:unix: LIBS += -L$$PWD/fmod/lib/ -lfmod_vc

INCLUDEPATH += $$PWD/fmod
DEPENDPATH += $$PWD/fmod

unix|win32: LIBS += -lfmod_vc
