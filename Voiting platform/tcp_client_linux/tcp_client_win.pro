TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -lws2_32
SOURCES += main.c \
    concat.c \
    init.c \
    coding_comtoint.c \
    read_package.c \
    send_package.c

HEADERS += \
    client.h
