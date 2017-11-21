TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS -= lws2_32

SOURCES += main.c \
    readn.c \
    decoder.c \
    concat.c \
    sendmsg.c

HEADERS += \
    client.h
