# -------------------------------------------------
# Project created by QtCreator 2010-06-10T09:25:43
# -------------------------------------------------
QT -= gui
TARGET = powersetDebug
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app

include(../logmacros.pri)

HEADERS += \
		activelogs.h \
		printpowerset.h
SOURCES += \
	main.cpp \
    printpowerset.cpp
