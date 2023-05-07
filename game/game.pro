
QT += core gui
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    creature.cpp \
    defeat.cpp \
    defenceedit.cpp \
    gamedata.cpp \
    gamestart.cpp \
    main.cpp \
    mainedit.cpp \
    mainwindow.cpp \
    mapin.cpp \
    mapout.cpp \
    modechoose.cpp \
    model.cpp \
    mybutton.cpp \
    soundchoose.cpp

HEADERS += \
    creature.h \
    defeat.h \
    defenceedit.h \
    gamedata.h \
    gamestart.h \
    mainedit.h \
    mainwindow.h \
    mapin.h \
    mapout.h \
    modechoose.h \
    model.h \
    mybutton.h \
    soundchoose.h

FORMS += \
    defenceedit.ui \
    gamestart.ui \
    mainedit.ui \
    mainwindow.ui \
    mapin.ui \
    mapout.ui \
    modechoose.ui \
    model.ui \
    soundchoose.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc
