#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <pthread.h>
#include <dir.h>
#include <stdbool.h>
#define NEW 1
#define ADD 2
#define REMOVE 3
#define LIST 4
#define OPEN 5
#define CLOSE 6
#define VOTE 7
#define DISCONNECT 8
#define HELP 9
char CURRENT_DIR[50];
char *answer;
typedef struct args_tag {
    int socket;
    char *ip;
    int port;
} args_t;
args_t args;
// Соединить две строки
char *concat(char *s1, char *s2);
// Удержание соединения для пользователя
void *connection_handler(void *socket_desc);
// Чтение сообщения от клиента
int readn(int *socket,char* output);
// Добавить новую тему
void add_theme(char *name);
// Добавить альтернативу выбора в теме
void add_alt(char *theme, char *alt);
// Удаляем тему со всеми альтернативами
void remove_theme(char *name);
// Отправка ответа клиенту
int sendmsg(int *socket);
#endif // SERVER_H
