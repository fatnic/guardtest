TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lsfml-window -lsfml-graphics -lsfml-system -lz

# sfml-tmxloader & pugixml
INCLUDEPATH += $$PWD/external/sfml-tmxloader/include
SOURCES     += $$PWD/external/sfml-tmxloader/src/*.cpp \
    entity.cpp \
    guard.cpp
SOURCES     += $$PWD/external/sfml-tmxloader/src/pugixml/pugixml.cpp

SOURCES += main.cpp \
    game.cpp \
    maingame.cpp

DISTFILES += \
    guardtest.pro.user

HEADERS += \
    game.hpp \
    gamestate.hpp \
    maingame.hpp \
    entity.hpp \
    guard.hpp \
    common.hpp

