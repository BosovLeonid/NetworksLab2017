TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lws2_32

SOURCES += main.c \
    add_alt.c \
    add_theme.c \
    concat.c \
    connection_handler.c \
    readn.c \
    remove_theme.c \
    sendmsg.c \
    help.c \
    list.c \
    change.c \
    vote.c \
    check.c

HEADERS += \
    server.h
