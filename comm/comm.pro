TEMPLATE = app
CONFIG += console c++17
CONFIG += c++20
CONFIG -= app_bundle

QT += core
QT += sql

SOURCES += \
        chat.cpp \
        groupchat.cpp \
        main.cpp \
        message.cpp \
        post.cpp

HEADERS += \
    chat.h \
    groupchat.h \
    message.h \
    post.h


HEADERS += ../profiles/profile.h

SOURCES += ../profiles/profile.cpp
