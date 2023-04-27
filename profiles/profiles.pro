TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        aquarium.cpp \
        fish.cpp \
        groupaquarium.cpp \
        main.cpp \
        profile.cpp

HEADERS += \
    aquarium.h \
    fish.h \
    groupaquarium.h \
    profile.h

HEADERS += ../comm_database/database.h

SOURCES += ../comm_database/databse.cpp

HEADERS += ../groups/group.h

SOURCES += ../groups/group.cpp
