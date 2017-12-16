TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lws2_32

SOURCES += main.c \
    add_alt.c \
    add_theme.c \
    concat.c \
    remove_theme.c \
    change.c \
    vote.c \
    check.c \
    thread_handler.c \
    get_help.c \
    get_list.c \
    send_package.c \
    read_package.c

HEADERS += \
    server.h
