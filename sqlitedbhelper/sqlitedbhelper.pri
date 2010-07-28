QT += \
    core \
    sql

include(../common/common.pri)

SOURCES += \
    $$PWD/SqliteDbHelper.cpp

HEADERS += \
    $$PWD/SqliteDbHelper.h
