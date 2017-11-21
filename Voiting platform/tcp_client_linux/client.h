#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#define BUFLEN 1024
#define HELP 0
#define NEW 1
#define ADD 2
#define REMOVE 3
#define LIST 4
#define CHECK 5
#define CHANGE 6
#define VOTE 7
#define DISCONNECT 8
//
int readn(int *socket,char* output);
// Отправка сообщения серверу
int sendmsg_to(int socket, char *msg);
// Соединить две строки
char* concat(char *s1, char *s2);
// Кодирование команды
int decoder(char *command);
#endif // CLIENT_H
