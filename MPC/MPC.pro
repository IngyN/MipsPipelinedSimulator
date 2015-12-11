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
    IFormat.cpp \
    Instruction.cpp \
    JFormat.cpp \
    main.cpp \
    mainwindow.cpp \
    RFormat.cpp \
    Simulator.cpp \
    simulatorwindow.cpp \
    CPU.cpp \
    inputException.cpp \
    InstructionT.cpp


HEADERS  += \
    IFormat.h \
    Instruction.h \
    JFormat.h \
    mainwindow.h \
    RFormat.h \
    Simulator.h \
    simulatorwindow.h \
    CPU.h \
    inputException.h \
    InstructionT.h

FORMS    += \
    mainwindow.ui \
    simulatorwindow.ui

