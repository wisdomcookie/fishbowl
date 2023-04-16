QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    home.cpp

HEADERS += \
    home.h

FORMS += \
    createNewChat.ui \
    createPost.ui \
    editFishProfile.ui \
    editProfile.ui \
    fish.ui \
    fishProfile.ui \
    friends.ui \
    group.ui \
    groups.ui \
    home.ui \
    login.ui \
    messages.ui \
    post.ui \
    profile.ui \
    search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
