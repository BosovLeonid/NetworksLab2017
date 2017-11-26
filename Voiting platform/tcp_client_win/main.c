#include <client.h>
int main(int argc , char *argv[])
{
    char buffer[BUFLEN];
    char answer[BUFLEN];
    char *msg = "";
    int limit_of_votes = 10;
    bool is_auth = false;

    setlocale(LC_ALL, "Rus");

    printf("Voiting/raiting client ver.3\n");
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

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("\nEnter your nickname:\n");
    while(!is_auth){
        memset(buffer,0,strlen(buffer));
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightRed));
        printf("\nNickname: ");
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGray));
        fgets(buffer, BUFLEN, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        char *tmp = buffer;
        char *data = strtok_r(tmp, " ", &tmp);
        char *trash = strtok_r(tmp, " ", &tmp);
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
        int n = sendmsg(csocket, msg);
        if( n < 0 ){
            perror("Error writing to socket.\n");
            return 1;
        }
        int l = readn(csocket, answer);
        if ( l < 0 ){
            printf("Error reading from socket.\n");
            return 1;
        }
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
        printf("\nAnswer from server:\n\n");
        printf("*******************************************************************************\n");
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGray));
        if(strcmp(answer,"Error.\n") == 0){
            printf("This nickname is already in database.\n");
            SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
            printf("*******************************************************************************\n");
            continue;
        }
        else{
            is_auth = true;
            printf("You logined as %s.\n", data);
        }
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
        printf("*******************************************************************************\n");
    }

    while(1){
        memset(buffer,0,strlen(buffer));
        memset(answer,0,strlen(answer));
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | White));
        printf("You have %d votes to vote.\n", limit_of_votes);
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightRed));
        printf("\nEnter command: ");
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGray));
        fgets(buffer, BUFLEN, stdin);
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
        printf("\nAnswer from server:\n\n");
        printf("*******************************************************************************\n");
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | LightGray));
        buffer[strlen(buffer) - 1] = '\0';
        char *tmp = buffer;
        char *com = strtok_r(tmp, " ", &tmp);
        char *theme = strtok_r(tmp, " ", &tmp);
        char *alt = strtok_r(tmp, " ", &tmp);
        char *votes = strtok_r(tmp, " ", &tmp);
        char *trash = strtok_r(tmp, " ", &tmp);
        msg = "";
        int key = decoder(com);
        switch(key){
            case HELP:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case NEW:  {
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                if( alt != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case ADD: {
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                msg = concat(msg, " ");
                if( alt == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, alt);
                if( votes != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case REMOVE:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                if( alt != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }

                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case LIST:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case CHECK:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                if( alt != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);
                break;
            }
            case CHANGE:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                if( alt != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                printf(answer);

                break;
            }
            case VOTE:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                msg = concat(msg, " ");
                if( theme == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, theme);
                msg = concat(msg, " ");
                if( alt == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                msg = concat(msg, alt);
                msg = concat(msg, " ");
                if( votes == NULL ){
                    printf("Too few arguments. Try again.\n");
                    break;
                }
                if (limit_of_votes < atoi(votes)){
                    printf("Count of votes more then your limit.\n");
                    break;
                }
                msg = concat(msg, votes);
                if( trash != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                    return 1;
                }
                char *tmp_answer = answer;
                if(strcmp("Error:", strtok_r(tmp_answer," ", &tmp_answer)) == 0){
                    printf("Error: %s", tmp_answer);
                    break;
                }
                printf("%s %s", answer, tmp_answer);
                limit_of_votes = limit_of_votes - atoi(votes);
                break;
            }
            case DISCONNECT:{
                char msg_key[1];
                itoa(key, msg_key, 10);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 1;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                return 0;
            }
            default:    {
                printf("Command %s not found.\n", com);
                printf("Type ""help"" to get list of available commands.\n");
                break;
            }
        }
        SetConsoleTextAttribute(hConsole, (WORD) ((Black << 4) | Yellow));
        printf("*******************************************************************************\n");
    }
    return 1;
}
