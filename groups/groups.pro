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

SOURCES += ../admin/administrator.cpp
SOURCES += ../profiles/profile.cpp
SOURCES +=
SOURCES += ../profiles/fish.cpp
SOURCES += ../profiles/aquarium.cpp
SOURCES += ../comm/post.cpp

HEADERS += ../admin/administrator.h
HEADERS +=
HEADERS +=
HEADERS += ../profiles/fish.h
HEADERS += ../profiles/aquarium.h
HEADERS += ../comm/post.h
