TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
QT += opengl
LIBS += -lfreeglut

SOURCES += main.cpp \
    RgbImage.cpp

HEADERS += \
    materiais.hpp \
    Camera.hpp \
    Bullet.hpp \
    main.hpp \
    Map.hpp \
    Map.hpp.autosave \
    Wall.hpp \
    Colors.hpp \
    BoundingBox.hpp \
    Target.hpp \
    HUD.hpp \
    Sounds.hpp \
    Images.hpp \
    RgbImage.h \
    Model.hpp \
    Events.hpp \
    Lights.hpp \
    ModelsTargetsExtras.hpp \
    Physics.hpp \
    Ground.hpp

OTHER_FILES += \
    CG_FPS_project.pro.user \
    models_textures/textures/grass_tex.bmp \
    models_textures/textures/ground_tex.bmp \
    models_textures/textures/grass_tex.jpg \
    models_textures/textures/ground_tex.jpg \
    NOTA_SOBRE_FICHEIROS.txt



#INCLUDEPATH += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\inc
#INCLUDEPATH += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\lib

#LIBS += C:\\"Program Files (x86)"\\"FMOD SoundSystem"\\"FMOD Programmers API Windows"\api\lib\fmodex_vc.lib

#unix|win32: LIBS += -L$$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api/lib/ -lfmodex_vc

#INCLUDEPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api
#DEPENDPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/api

#INCLUDEPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/lib
#DEPENDPATH += $$PWD/../../../../../../"Program Files (x86)"/"FMOD SoundSystem"/"FMOD Programmers API Windows"/lib

# FMOD library .libfiles
LIBS += -lfmodex_vc
LIBS += -lfmodexL_vc

# SFML library .libfiles
LIBS += -lsfml-audio
LIBS += -lsfml-audio-d
LIBS += -lsfml-audio-s
LIBS += -lsfml-audio-s-d
#LIBS += -lopenall32
#LIBS += -lsfml-audio-2
#LIBS += -lsfml-audio-2-d
#LIBS += -llibsndfile-1

# DevIL library .lib files
LIBS += -lDevIL
LIBS += -lILU
LIBS += -lILUT

# Path to the DevIL library
#LIBS += -L"C:/Users/AntónioCarlosLagarto/Desktop/DevIL-SDK-x86-1.7.8/lib"

# Path to header files directory
#INCLUDEPATH += "C:/Users/AntónioCarlosLagarto/Desktop/DevIL-SDK-x86-1.7.8/include/IL"
