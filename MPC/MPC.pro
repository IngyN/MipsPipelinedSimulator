#-------------------------------------------------
#
# Project created by QtCreator 2015-12-11T17:24:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MPC
TEMPLATE = app


SOURCES += \
    main.cpp \
    simulatorwindow.cpp \
    CPU.cpp \
    inputException.cpp \
    InstructionT.cpp


HEADERS  += \
    Instruction.h \
    simulatorwindow.h \
    CPU.h \
    inputException.h \
    InstructionT.h

FORMS    += \
    mainwindow.ui \
    simulatorwindow.ui

