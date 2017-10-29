#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>
#include <string.h>
#define NEW 1
#define ADD 2
#define REMOVE 3
#define LIST 4
#define OPEN 5
#define CLOSE 6
#define VOTE 7
#define DISCONNECT 8
#define HELP 9
int readn(int *socket,char* output);
int decoder(char *command);
#endif // CLIENT_H
