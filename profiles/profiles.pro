TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        aquarium.cpp \
        fish.cpp \
        main.cpp \
        profile.cpp

HEADERS += \
    aquarium.h \
    fish.h \
    profile.h

FORMS +=
