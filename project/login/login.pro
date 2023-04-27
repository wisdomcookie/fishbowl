TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        login.cpp \
        main.cpp

HEADERS += \
    login.h

HEADERS += ../comm_database/database.h

SOURCES += ../comm_database/database.cpp
