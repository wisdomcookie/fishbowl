TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        engine.cpp \
        main.cpp \
        session.cpp \
        database.cpp

HEADERS += \
    engine.h \
    session.h \
    database.h

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

#HEADERS += ../admin/administrator.h
HEADERS += ../profiles/profile.h
HEADERS += ../profiles/fish.h
HEADERS += ../profiles/aquarium.h

#SOURCES += ../admin/administrator.cpp
SOURCES += ../profiles/profile.cpp
SOURCES += ../profiles/fish.cpp
SOURCES += ../profiles/aquarium.cpp
