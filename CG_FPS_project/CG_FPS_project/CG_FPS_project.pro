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
    Sounds.hpp

OTHER_FILES += \
    CG_FPS_project.pro.user \
    models_textures/textures/grass_tex.bmp \
    models_textures/textures/ground_tex.bmp \
    models_textures/textures/grass_tex.jpg \
    models_textures/textures/ground_tex.jpg \
    NOTA_SOBRE_FICHEIROS.txt \
    fmodex.dll


INCLUDEPATH += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\inc
INCLUDEPATH += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\lib

LIBS += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\lib\fmodex_vc.lib

unix|win32: LIBS += -L$$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api/lib/ -lfmodex_vc

INCLUDEPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api
DEPENDPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api

INCLUDEPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/lib
DEPENDPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/lib
