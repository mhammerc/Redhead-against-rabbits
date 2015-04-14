TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    game.cpp

LIBS += -L"/home/imote/Development/SFML-2.2/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += "/home/imote/Development/SFML-2.2/include"
DEPENDPATH += "/home/imote/Development/SFML-2.2/include"

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    game.h

