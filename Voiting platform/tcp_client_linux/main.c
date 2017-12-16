#include <client.h>
const char *LOCALE = "Rus";
int main(int argc , char *argv[])
{
    char buffer[BUFLEN_MAX];
    char answer[BUFLEN_MAX];
    char *msg = "";
    int limit_of_votes = 10;
    bool is_auth = false;

    setlocale(LC_ALL, LOCALE);
    printf("Voiting/raiting client ver.4\n");
    printf("Client starting...\n");

    if (argc < 3) {
        printf("Params ERROR.\nExample:client-win ""server_ip"" ""server_port""\n\n");
        exit(0);
    }

    csocket = init(argc, argv);
    if(csocket < 1){
        exit(-1);
    }
    else
        printf("Connected to server.\n");

    printf("\nEnter your nickname:\n");
    while(!is_auth){
        memset(buffer,0,sizeof(buffer));
        memset(answer, 0, sizeof(answer));
        printf("\nNickname: ");
        fgets(buffer, BUFLEN_MAX, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        char *saveptr;
        char *data = strtok_r(buffer, " ", &saveptr);
        char *trash = strtok_r(NULL, " ", &saveptr);
        if(data == NULL){
            printf("You did not enter anything.\n");
            continue;
        }
        msg = "9 ";
        msg = concat(msg, data);
        if(trash != NULL){
            printf("You entered too much.\n");
            continue;
        }
        send_read(csocket, msg, answer);
        if(strcmp(answer,"Error.\n") == 0){
            printf("This nickname is already in database.\n");
            printf("*******************************************************************************\n");
            continue;
        }
        else{
            is_auth = true;
            printf("You logined as %s.\n", data);
        }
        printf("*******************************************************************************\n");
    }

    while(1){
        free(buffer);
        free(answer);
        memset(buffer, 0, sizeof(buffer));
        memset(answer, 0, sizeof(answer));
        printf("You have %d votes to vote.\n", limit_of_votes);
        printf("\nEnter command: ");
        fgets(buffer, BUFLEN_MAX, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        char *saveptr;
        char *com_argv[4];
        char *com = strtok_r(buffer, " ", &saveptr);
        com_argv[1] = strtok_r(NULL, " ", &saveptr);
        com_argv[2] = strtok_r(NULL, " ", &saveptr);
        com_argv[3] = strtok_r(NULL, " ", &saveptr);
        com_argv[4] = strtok_r(NULL, " ", &saveptr);
        msg = "";
        if (com == NULL){
            printf("\nYou did not enter anything!\n\n");
            continue;
        }
        int key = coding_comToInt(com);
        switch(key){
            case HELP:{
                msg = make_massage(0, com_argv, key);
                if(strcmp(msg, "Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case NEW:  {
                msg = make_massage(1, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case ADD: {
                msg = make_massage(2, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case REMOVE:{
                msg = make_massage(1, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case LIST:{
                msg = make_massage(0, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case CHECK:{
                msg = make_massage(1, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case CHANGE:{
                msg = make_massage(1, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                break;
            }
            case VOTE:{
                msg = make_massage(3, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                char *tmp_answer = answer;
                if(strcmp("Error:", strtok_r(tmp_answer," ", &saveptr)) == 0){
                    printf("Error: %s", tmp_answer);
                    break;
                }
                printf("%s %s", answer, saveptr);
                limit_of_votes = limit_of_votes - atoi(com_argv[3]);
                break;
            }
            case DISCONNECT:{
                msg = make_massage(0, com_argv, key);
                if(strcmp(msg,"Error") == 0)
                    break;
                send_read(csocket, msg, answer);
                printf(answer);
                return 0;
            }
            default:    {
                printf("Command %s not found.\n", com);
                printf("Type ""help"" to get list of available commands.\n");
                break;
            }
        }
        printf("*******************************************************************************\n");
    }
    return 1;
}

char *make_massage(int argc, char *argv[], int key){
    char msg_key[2];
    char *massage;
    snprintf(msg_key, sizeof(msg_key), "%d", key);
    int i = 0;
    for(i = 1; i <= argc; i++){
        if(argv[i] == NULL){
            printf("\nToo few arguments. Try again.\n\n");
            return "Error";
        }
    }
    if(argv[argc + 1] != NULL){
        printf("\nToo much arguments. Try again.\n\n");
        return "Error";
    }
    massage = msg_key;
    for(i = 1; i <= argc; i++){
        massage = concat(massage, " ");
        massage = concat(massage, argv[i]);
    }
    return massage;
}

void send_read(int sock, char *massage, char *output){
        char *tmp = massage;
        if(send_package(sock, tmp) < 0)
            exit(-1);
        if(read_package(sock, output) < 0)
            exit(-1);
        printf("\nAnswer from server:\n\n");
        printf("*******************************************************************************\n");
        return;
}
