TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        group.cpp \
        main.cpp

HEADERS += \
    group.h

#SOURCES += ../admin/administrator.cpp
SOURCES += ../profiles/profile.cpp
#SOURCES += ../profiles/person.cpp
SOURCES += ../profiles/fish.cpp
SOURCES += ../profiles/aquarium.cpp
SOURCES += ../comm/post.cpp

#HEADERS += ../admin/administrator.h
HEADERS += ../profiles/profile.h
#HEADERS += ../profiles/person.h
HEADERS += ../profiles/fish.h
HEADERS += ../profiles/aquarium.h
HEADERS += ../comm/post.h
