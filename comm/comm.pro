TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

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
