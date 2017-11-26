#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <dir.h>
#include <stdbool.h>
#include <windows.h>
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
#define AUTHORIZATION 9
char CURRENT_DIR[50];
char *answer;
int g_error;
typedef struct args_tag {
    int socket;
    char *ip;
    int port;
} args_t;
args_t args;
// Соединить две строки
char *concat(char *s1, char *s2);
// Удержание соединения для пользователя
DWORD WINAPI *connection_handler(void *socket_desc);
// Чтение сообщения от клиента
int readn(int socket,char* output);
// Отправка сообщения клиенту
int sendmsg(int socket);
// Получение информации о командах
char *help();
// Добавить новую тему
void add_theme(char *name);
// Добавить альтернативу выбора в теме
void add_alt(char *theme, char *alt);
// Удаляем тему со всеми альтернативами
void remove_theme(char *name);
// Получение списка тем
char *list();
// Получить информацию об определенной теме
void check(char *theme);
// Изменить состояне темы(открыта/закрыта)
void change(char *theme);
// Проголосовать за альтернативу в теме
void vote(char *theme, char *alt, int votes);

#endif // SERVER_H
