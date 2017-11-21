#include <server.h>
struct user{
    int socket;
    char *ip;
    int port;
    int id;
};

struct user users[20];
int nextUser = 0;

static const struct user ClearUser;
// Удерживаем соединение для каждого пользователя
DWORD WINAPI *connection_handler(void *args)
{
    args_t *arg = (args_t*) args;

    //Get the socket descriptor
    int csocket = arg->socket;
    char buffer[BUFLEN];

    int user_id = nextUser;
    users[nextUser].socket = arg->socket;
    users[nextUser].id = nextUser;
    users[nextUser].ip = arg->ip;
    users[nextUser].port = arg->port;

    nextUser = nextUser + 1;
    while(1){
        int len = readn(csocket, buffer);
        if(len == -1)
        {
           return 10;
        }
        char *tmp = buffer;
        char *tmp1 = strtok(tmp, " ");
        int command = atoi(tmp1);
        switch(command){
            case HELP:{
                answer = help();
                printf("Sending help to %d.\n", csocket);
                int n = sendmsg(csocket);
                if ( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case NEW:  {
                char *theme = strtok(NULL," ");
                add_theme(theme);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case ADD:{
                char *theme = strtok(NULL," ");
                char *alt = strtok(NULL, " ");
                add_alt(theme, alt);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if (n < 0) {
                   perror("Error writing to socket.\n");
                   return 0;
                }
            break;
            }
            case REMOVE:{
                char *theme = strtok(NULL," ");
                remove_theme(theme);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case LIST:{
                answer = list();
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if ( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case CHECK:{
                char *theme = strtok(NULL," ");
                check(theme);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case CHANGE:{
                char *theme = strtok(NULL, " ");
                change(theme);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if ( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case VOTE:{
                char *theme = strtok(NULL, " ");
                char *alt = strtok(NULL, " ");
                int votes = atoi(strtok(NULL, " "));
                vote(theme, alt, votes);
                printf("Sending answer to %d.\n", csocket);
                int n = sendmsg(csocket);
                if ( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
            case DISCONNECT:{
                printf("Closing connection to %s:%d\n", users[user_id].ip, users[user_id].port);
                answer = "You have been disconnected.\n";
                printf("Sending answer to %d and disconnecting him.\n", csocket);
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("Error writing to socket.\n");
                    return 0;
                }
                closesocket(users[user_id].socket);
                nextUser = user_id;
                users[user_id] = ClearUser;
                break;
            }
            default:    {
                printf("Command %d not found\n", command);
                answer = "Something goes wrong, try again.\n";
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("Error writing to socket.\n");
                    return 0;
                }
                break;
            }
        }
    }
}
