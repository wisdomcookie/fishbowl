TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core
QT += sql

SOURCES += \
        main.cpp \
        results.cpp \
        searchengine.cpp

HEADERS += \
    results.h \
    searchengine.h
