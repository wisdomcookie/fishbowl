TEMPLATE = app
CONFIG += console c++17
CONFIG += c++20
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        groupchat.cpp \
        main.cpp \
        message.cpp \
        post.cpp \
        postcomment.cpp

HEADERS += \
    groupchat.h \
    message.h \
    post.h \
    postcomment.h

#HEADERS += ../admin/administrator.h
HEADERS += ../profiles/profile.h
HEADERS += ../profiles/fish.h
HEADERS += ../profiles/aquarium.h

#SOURCES += ../admin/administrator.cpp
SOURCES += ../profiles/profile.cpp
SOURCES += ../profiles/fish.cpp
SOURCES += ../profiles/aquarium.cpp

HEADERS += ../groups/group.h
SOURCES += ../groups/group.cpp
