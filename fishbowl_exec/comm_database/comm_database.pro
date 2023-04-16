TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        database.cpp \
        main.cpp

HEADERS += \
    database.h
