TEMPLATE = app
TARGET = winfoc

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += window.h tconvert.h minterface.h uniqueloggername.h mymacros.h
SOURCES +=  main.cpp window.cpp tconvert.cpp minterface.cpp uniqueloggername.cpp
