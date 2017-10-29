#include <server.h>
struct user{
    int socket;
    char *ip;
    int port;
    int id;
};

pthread_t threads[10];
struct user users[10];
int nextUser = 0;

static const struct user ClearUser;
// Удерживаем соединение для каждого пользователя
void *connection_handler(void *args)
{
    args_t *arg = (args_t*) args;

    //Get the socket descriptor
    int csocket = arg->socket;
    char buffer[256];

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
        case NEW:  {
            char *theme = strtok(NULL," ");
            add_theme(theme);
            int n = sendmsg(csocket);
            if (n < 0) {
                perror("ERROR writing to socket\n");
                return 0;
            }
            break;
        }
        case ADD:{
            char *theme = strtok(NULL," ");
            int count_of_alts = atoi(strtok(NULL," "));
            int i;
            for (i = count_of_alts; count_of_alts != 0; count_of_alts--)
            {
                add_alt(theme, strtok(NULL," "));
                int n = sendmsg(csocket);
                if (n < 0) {
                    perror("ERROR writing to socket\n");
                    return 0;
                }
            }
            break;
        }
        case REMOVE:{
            char *theme = strtok(NULL," ");
            remove_theme(theme);
            int n = sendmsg(csocket);
            if (n < 0) {
                perror("ERROR writing to socket\n");
                return 0;
            }
            break;
        }
        case LIST:{
            break;
        }
        case OPEN:{
            break;
        }
        case CLOSE:{
            break;
        }
        case VOTE:{
            break;
        }
        case DISCONNECT:{
            printf("Closing connection to %s:%d\n", users[user_id].ip, users[user_id].port);
            answer = "You have been disconnected.";
            int n = sendmsg(csocket);
            if (n < 0) {
                perror("ERROR writing to socket\n");
                return 0;
            }
            closesocket(users[user_id].socket);
            nextUser = user_id;
            users[user_id] = ClearUser;
            break;
        }
        case HELP:{
            break;
        }
        default:    {
            printf("Command %d not found\n",command);
            answer = "Something goes wrong, try again.";
            int n = sendmsg(csocket);
            if (n < 0) {
                perror("ERROR writing to socket\n");
                return 0;
            }
            break;
        }
    }
    }
}
