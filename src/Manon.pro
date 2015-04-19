TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    scenenode.cpp \
    spritenode.cpp \
    entity.cpp \
    aircraft.cpp \
    world.cpp \
    command.cpp \
    commandqueue.cpp \
    player.cpp \
    application.cpp \
    gamestate.cpp \
    loadingstate.cpp \
    menustate.cpp \
    paralleltask.cpp \
    pausestate.cpp \
    state.cpp \
    statestack.cpp \
    titlestate.cpp \
    utility.cpp \
    button.cpp \
    component.cpp \
    container.cpp \
    label.cpp \
    settingsstate.cpp \
    datatables.cpp \
    gameoverstate.cpp \
    pickup.cpp \
    projectile.cpp \
    textnode.cpp \
    tilemapnode.cpp \
    character.cpp

LIBS += -L"/home/imote/Development/SFML-2.2/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

INCLUDEPATH += "/home/imote/Development/SFML-2.2/include"
DEPENDPATH += "/home/imote/Development/SFML-2.2/include"

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    resourceholder.h \
    resourceholder.inl \
    resourceidentifiers.h \
    scenenode.h \
    spritenode.h \
    entity.h \
    aircraft.h \
    world.h \
    category.h \
    command.h \
    commandqueue.h \
    player.h \
    application.h \
    gamestate.h \
    loadingstate.h \
    menustate.h \
    paralleltask.h \
    pausestate.h \
    state.h \
    stateidentifiers.h \
    statestack.h \
    titlestate.h \
    utility.h \
    button.h \
    component.h \
    container.h \
    label.h \
    settingsstate.h \
    datatables.h \
    gameoverstate.h \
    pickup.h \
    projectile.h \
    textnode.h \
    tilemapnode.h \
    rabbits_level.h \
    character.h
