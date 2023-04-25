TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
QT += core
QT += sql

SOURCES += \
        administrator.cpp \
        main.cpp \
        report.cpp

HEADERS += \
    administrator.h \
    report.h

HEADERS += ../profiles/profile.h

SOURCES += ../profiles/profile.cpp

