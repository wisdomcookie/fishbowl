TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        main.cpp

HEADERS += ../engine/engine.h \
           ../comm_database/database.h \
           ../groups/group.h \
           ../Gui/home.h \
           ../login/login.h \
           ../profiles/profile.h \
           test.h

SOURCES += ../engine/engine.cpp \
           ../comm_database/database.cpp \
           ../groups/group.cpp \
           ../Gui/home.cpp \
           ../login/login.cpp \
           ../profiles/profile.cpp \
           test.cpp
