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
#define AUTHORIZATION 9
char CURRENT_DIR[256];
char *answer;
typedef struct args_tag {
    int socket;
    char *ip;
    int port;
} args_t;
args_t args;
// Соединить две строки
char *concat(char *s1, char *s2);
// Обработчик потока, выполняемый для подключившегося клиента
DWORD WINAPI *thread_handler(void *socket_desc);
// Чтение пакета от клиента
// Пакет - количество байт, которые надо принять(отправить),
// и команда от клиента(ответ сервера на команду)
int read_package(int socket,char* output);
// Отправка пакета клиенту
int send_package(int socket);
// Получение информации о командах
char *get_help();
// Добавить новую тему
void add_theme(char *name);
// Добавить альтернативу выбора в теме
void add_alt(char *theme, char *alt);
// Удаляем тему со всеми альтернативами
void remove_theme(char *name);
// Получение списка тем
char *get_list();
// Получить информацию об определенной теме
void check(char *theme);
// Изменить состояне темы(открыта/закрыта)
void change(char *theme);
// Проголосовать за альтернативу в теме
void vote(char *theme, char *alt, int votes);
// Проверка открытия файла
int check_file(FILE *file, char* path);
// Проверка наличия темы
int check_theme(bool flag, char* theme, char *PATH);
// Авторизация клиента
void authorize(char *username, int sock, int id);
#endif // SERVER_H
