TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    engine/scenenode.cpp \
    engine/spritenode.cpp \
    engine/entity.cpp \
    engine/command.cpp \
    engine/commandqueue.cpp \
    engine/paralleltask.cpp \
    engine/state.cpp \
    engine/statestack.cpp \
    engine/utility.cpp \
    engine/gui/button.cpp \
    engine/gui/component.cpp \
    engine/gui/container.cpp \
    engine/gui/label.cpp \
    engine/textnode.cpp \
    engine/animatedspritenode.cpp \
    title/titlestate.cpp \
    game/animationtable.cpp \
    game/character.cpp \
    game/datatables.cpp \
    game/gamestate.cpp \
    game/level_datatables.cpp \
    game/player.cpp \
    game/tilemapnode.cpp \
    game/world.cpp \
    gameover/gameoverstate.cpp \
    loading/loadingstate.cpp \
    menu/menustate.cpp \
    pause/pausestate.cpp \
    settings/settingsstate.cpp \
    application.cpp \
    game/pathtable.cpp

LIBS += -L"/home/imote/Development/SFML-build/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/home/imote/Development/SFML/include"
DEPENDPATH += "/home/imote/Development/SFML/include"

HEADERS += \
    engine/resourceholder.h \
    engine/resourceholder.inl \
    engine/scenenode.h \
    engine/spritenode.h \
    engine/entity.h \
    engine/command.h \
    engine/commandqueue.h \
    engine/paralleltask.h \
    engine/state.h \
    engine/statestack.h \
    engine/utility.h \
    engine/gui/button.h \
    engine/gui/component.h \
    engine/gui/container.h \
    engine/gui/label.h \
    engine/textnode.h \
    engine/animatedspritenode.h \
    game/animationtable.h \
    game/category.h \
    game/character.h \
    game/datatables.h \
    game/gamestate.h \
    game/player.h \
    game/tilemapnode.h \
    game/world.h \
    gameover/gameoverstate.h \
    loading/loadingstate.h \
    menu/menustate.h \
    pause/pausestate.h \
    title/titlestate.h \
    stateidentifiers.h \
    resourceidentifiers.h \
    settings/settingsstate.h \
    application.h \
    game/pathtable.h
