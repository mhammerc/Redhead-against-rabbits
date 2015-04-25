TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    engine/scenenode.cpp \
    engine/spritenode.cpp \
    engine/entity.cpp \
    world.cpp \
    engine/command.cpp \
    engine/commandqueue.cpp \
    player.cpp \
    application.cpp \
    gamestate.cpp \
    loadingstate.cpp \
    menustate.cpp \
    engine/paralleltask.cpp \
    pausestate.cpp \
    engine/state.cpp \
    engine/statestack.cpp \
    titlestate.cpp \
    engine/utility.cpp \
    engine/gui/button.cpp \
    engine/gui/component.cpp \
    engine/gui/container.cpp \
    engine/gui/label.cpp \
    settingsstate.cpp \
    datatables.cpp \
    gameoverstate.cpp \
    engine/textnode.cpp \
    tilemapnode.cpp \
    character.cpp \
    level_datatables.cpp \
    engine/animatedspritenode.cpp \
    animationtable.cpp

LIBS += -L"/home/imote/Development/SFML-build/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/home/imote/Development/SFML/include"
DEPENDPATH += "/home/imote/Development/SFML/include"

HEADERS += \
    engine/resourceholder.h \
    engine/resourceholder.inl \
    resourceidentifiers.h \
    engine/scenenode.h \
    engine/spritenode.h \
    engine/entity.h \
    world.h \
    category.h \
    engine/command.h \
    engine/commandqueue.h \
    player.h \
    application.h \
    gamestate.h \
    loadingstate.h \
    menustate.h \
    engine/paralleltask.h \
    pausestate.h \
    engine/state.h \
    stateidentifiers.h \
    engine/statestack.h \
    titlestate.h \
    engine/utility.h \
    engine/gui/button.h \
    engine/gui/component.h \
    engine/gui/container.h \
    engine/gui/label.h \
    settingsstate.h \
    datatables.h \
    gameoverstate.h \
    engine/textnode.h \
    tilemapnode.h \
    character.h \
    engine/animatedspritenode.h \
    animationtable.h
