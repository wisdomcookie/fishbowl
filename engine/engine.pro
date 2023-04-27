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

HEADERS += ../profiles/profile.h

SOURCES += ../profiles/profile.cpp

HEADERS += ../groups/group.h

SOURCES += ../groups/group.cpp

