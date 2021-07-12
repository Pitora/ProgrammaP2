#-------------------------------------------------
#
# Project created by QtCreator 2021-07-12T14:01:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ProgrammaP2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        window.cpp \
    additem.cpp \
    controller.cpp \
    Classes/armor.cpp \
    Classes/buff.cpp \
    Classes/character.cpp \
    Classes/collection.cpp \
    Classes/consumable.cpp \
    Classes/exceptions.cpp \
    Classes/healing.cpp \
    Classes/melee.cpp \
    Classes/object.cpp \
    Classes/ranged.cpp \
    Classes/tc.cpp \
    Classes/tdeep.cpp \
    Classes/weapon.cpp \
    codex.cpp

HEADERS += \
        window.h \
    additem.h \
    controller.h \
    Classes/armor.h \
    Classes/buff.h \
    Classes/character.h \
    Classes/collection.h \
    Classes/consumable.h \
    Classes/healing.h \
    Classes/melee.h \
    Classes/object.h \
    Classes/ranged.h \
    Classes/weapon.h \
    codex.h

DISTFILES += \
    Classes/data.xml