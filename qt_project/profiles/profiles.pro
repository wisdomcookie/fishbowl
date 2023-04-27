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

HEADERS += ../groups/group.h
SOURCES += ../groups/group.cpp

HEADERS += ../comm/groupchat.h
HEADERS += ../comm/message.h
HEADERS += ../comm/post.h
HEADERS += ../comm/postcomment.h

SOURCES += ../comm/groupchat.cpp
SOURCES += ../comm/message.cpp
SOURCES += ../comm/post.cpp
SOURCES += ../comm/postcomment.cpp


