TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        engine.cpp \
        main.cpp

HEADERS += \
    engine.h

HEADERS += ../profiles/profile.h

SOURCES += ../profiles/profile.cpp

HEADERS += ../comm_database/database.h

SOURCES += ../comm_database/databse.cpp

HEADERS += ../groups/group.h

SOURCES += ../groups/group.cpp

