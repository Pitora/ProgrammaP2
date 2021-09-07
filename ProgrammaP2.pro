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
        view/window.cpp \
    view/additem.cpp \
    view/codex.cpp \
    controller/controller.cpp \
    model/armor.cpp \
    model/buff.cpp \
    model/character.cpp \
    model/collection.cpp \
    model/consumable.cpp \
    model/healing.cpp \
    model/melee.cpp \
    model/object.cpp \
    model/ranged.cpp \
    model/tc.cpp \
    model/tdeep.cpp \
    model/weapon.cpp \
    model/stringm.cpp \
    view/smartcombobox.cpp \
    view/windowtabwidget.cpp


HEADERS += \
        view/window.h \
    view/additem.h \
    view/codex.h \
    controller/controller.h \
    model/armor.h \
    model/buff.h \
    model/character.h \
    model/collection.h \
    model/consumable.h \
    model/healing.h \
    model/melee.h \
    model/object.h \
    model/ranged.h \
    model/weapon.h \
    model/exceptions.h \
    model/stringm.h \
    view/smartcombobox.h \
    view/windowtabwidget.h


DISTFILES += \
    assets/b_char.png \
    assets/redboots_char.png \
    assets/redchest_char.png \
    assets/redgloves_char.png \
    assets/redhelm_char.png \
    assets/reditem1_char.png \
    assets/reditem2_char.png \
    assets/reditem3_char.png \
    assets/redsword_char.png \
    assets/scroll.jpg \
    assets/aimicon.png \
    assets/atkicon.png \
    assets/deficon.png \
    assets/dexicon.png \
    assets/stricon.png \
    assets/viticon.png \
    assets/cursor.png
