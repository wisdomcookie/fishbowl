QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    fishlisting.cpp \
    main.cpp \
    home.cpp \
    ../profiles/fish.cpp \
    ../profiles/profile.cpp

HEADERS += \
    fishlisting.h \
    home.h \
    ../profiles/fish.h \
    ../profiles/profile.h

FORMS += \
    #createNewChat.ui \
    #createPost.ui \
    #editFishProfile.ui \
    #editProfile.ui \
    #fish.ui \
    #fishProfile.ui \
    #friends.ui \
    #group.ui \
    #groups.ui \
    #fishlisting.ui \
    home.ui \
    #login.ui \
    #messages.ui \
    #post.ui \
    #profile.ui \
    #search.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    home.qrc
