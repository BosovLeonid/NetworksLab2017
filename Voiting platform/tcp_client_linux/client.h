#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define BUFLEN_MAX 2048
#define HELP 0
#define NEW 1
#define ADD 2
#define REMOVE 3
#define LIST 4
#define CHECK 5
#define CHANGE 6
#define VOTE 7
#define DISCONNECT 8
int csocket;
// Установка соединения с сервером
int init(int argc, char *argv[]);
// Чтение сообщения от сервера
int read_package(int socket, char *output);
// Отправка сообщения серверу
int send_package(int socket, char *msg);
// Соединить две строки
char* concat(char *s1, char *s2);
// Кодируем команду числом
int coding_comToInt(char *command);
char *make_massage(int argc, char *argv[], int key);
#endif // CLIENT_H
