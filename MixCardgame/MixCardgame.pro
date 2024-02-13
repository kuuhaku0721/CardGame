QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    generatetool.cpp \
    itemcard.cpp \
    main.cpp \
    mainwindow.cpp \
    master.cpp \
    mastercard.cpp \
    servent.cpp \
    serventcard.cpp \
    status.cpp

HEADERS += \
    generatetool.h \
    itemcard.h \
    mainwindow.h \
    master.h \
    mastercard.h \
    servent.h \
    serventcard.h \
    status.h

FORMS += \
    itemcard.ui \
    mainwindow.ui \
    mastercard.ui \
    serventcard.ui

TRANSLATIONS += \
    MixCardgame_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    res.qrc
