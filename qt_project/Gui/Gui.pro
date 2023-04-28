QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QT += core
QT += sql

SOURCES += \
    login.cpp \
    main.cpp \
    home.cpp \
    ../profiles/fish.cpp \
    ../profiles/profile.cpp \
    ../comm/message.cpp \
    ../comm/post.cpp \
    ../comm/postcomment.cpp \
    ../groups/group.cpp \
    ../engine/engine.cpp

HEADERS += \
    home.h \
    ../profiles/fish.h \
    ../profiles/profile.h \
    login.h \
    ../comm/message.h \
    ../comm/post.h \
    ../comm/postcomment.h \
    ../groups/group.h \
    ../engine/engine.h


FORMS += \
    login.ui \
    home.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    home.qrc
