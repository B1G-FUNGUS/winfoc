TEMPLATE = app
TARGET = winfoc

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

HEADERS += window.h log.h tconvert.h
SOURCES +=  main.cpp window.cpp log.cpp tconvert.cpp
