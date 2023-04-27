TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql
SOURCES += \
        group.cpp \
        main.cpp

HEADERS += \
    group.h

#HEADERS += ../admin/administrator.h
HEADERS += ../profiles/profile.h
HEADERS += ../profiles/fish.h
HEADERS += ../profiles/aquarium.h

#SOURCES += ../admin/administrator.cpp
SOURCES += ../profiles/profile.cpp
SOURCES += ../profiles/fish.cpp
SOURCES += ../profiles/aquarium.cpp

HEADERS += ../comm/groupchat.h
HEADERS += ../comm/message.h
HEADERS += ../comm/post.h
HEADERS += ../comm/postcomment.h

SOURCES += ../comm/groupchat.cpp
SOURCES += ../comm/message.cpp
SOURCES += ../comm/post.cpp
SOURCES += ../comm/postcomment.cpp
