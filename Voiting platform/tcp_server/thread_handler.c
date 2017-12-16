#include <server.h>
struct user{
    int socket;
    char *name;
    char *ip;
    int port;
    int id;
};

struct user users[20];
int nextUser = 0;

static const struct user ClearUser;

// Обработчик потока, выполняемый для подключившегося клиента
DWORD WINAPI *thread_handler(void *args)
{
    args_t *arg = (args_t*) args;

    // Get the socket descriptor
    int csocket = arg->socket;
    char buffer[BUFLEN_MAX];

    int user_id = nextUser;
    users[nextUser].socket = arg->socket;
    users[nextUser].id = nextUser;
    users[nextUser].ip = arg->ip;
    users[nextUser].port = arg->port;

    nextUser = nextUser + 1;
    while(1){
        free(buffer);
        memset(buffer, BUFLEN_MAX, sizeof(buffer));
        if(read_package(csocket, buffer) == 0)
        {
           return 1;
        }
        char *saveptr;
        char *com = strtok_r(buffer, " ", &saveptr);
        char *theme = strtok_r(NULL, " ", &saveptr);
        char *alt = strtok_r(NULL, " ", &saveptr);
        int votes = atoi(strtok_r(NULL, " ", &saveptr));
        int command = atoi(com);
        switch(command){
            case HELP:{
                answer = get_help();
                if (send_package(csocket) < 0 ){
                    return -1;
                }

                break;
            }
            case NEW:  {
                add_theme(theme);                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                break;
            }
            case ADD:{
                add_alt(theme, alt);                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
            break;
            }
            case REMOVE:{
                remove_theme(theme);                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                break;
            }
            case LIST:{
                answer = get_list();                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                free(answer);
                break;
            }
            case CHECK:{
                check(theme);
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                break;
            }
            case CHANGE:{
                change(theme);                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                break;
            }
            case VOTE:{
                vote(theme, alt, votes);                
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                break;
            }
            case DISCONNECT:{
                printf("Closing connection to %s:%d\n", users[user_id].ip, users[user_id].port);
                answer = "You have been disconnected.\n";
                if (send_package(csocket) < 0 ){
                    return -1;
                }
                closesocket(users[user_id].socket);
                nextUser = user_id;
                users[user_id] = ClearUser;
                return 0;
            }
            case AUTHORIZATION:{
                authorize(theme, csocket, user_id);
                break;
            }
            default:    {
                printf("Command %d not found\n", command);
                answer = "Something goes wrong, try again.\n";
                if (send_package(csocket) < 0) {
                    return -1;
                }
                break;
            }
        }
    }
}
// Проверка наличия файла
int check_file(FILE *file, char* path){
    if (file == NULL){
        printf("Error while opening file.\n");
        answer = "An error has occurred on server.\n";
        chdir(CURRENT_DIR);
        free(path);
        return -1;
    }
    return 0;
}
// Проверка наличия темы
int check_theme(bool flag, char *theme, char *PATH){
    if(!flag){
        answer = concat(theme, " doesn't exists.\n");
        chdir(CURRENT_DIR);
        free(PATH);
        return -1;
    }
    return 0;
}
// Авторизация клиента
void authorize(char *username, int sock, int id){
    char word_name[256], *tmp_name;
    FILE *auth;
    auth = fopen("auth.txt", "r+");
    if(auth == NULL){
         return;
    }
    answer = "Success.\n";
    while (fgets(word_name, sizeof(word_name), auth))
    {
    tmp_name = strtok(word_name,";");
    if(strcmp(tmp_name, username) == 0){
        answer = "Error.\n";
        break;
    }
    }
    if(strcmp(answer, "Success.\n") == 0){
        fprintf(auth, "%s;\n", username);
        users[id].name = username;
        printf("Socket %d logined as %s.\n", sock, users[id].name);
    }
    fclose(auth);
    if (send_package(sock) < 0){
        return;
    }
}
