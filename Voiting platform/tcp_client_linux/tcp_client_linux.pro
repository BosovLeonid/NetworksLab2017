TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    readn.c \
    decoder.c \
    concat.c \
    sendmsg_to.c

HEADERS += \
    client.h
