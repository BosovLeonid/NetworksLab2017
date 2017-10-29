TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    readn.c \
    decoder.c
LIBS += -lws2_32

HEADERS += \
    client.h
