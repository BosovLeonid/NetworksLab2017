#include <client.h>
int main(int argc , char *argv[])
{
    int csocket;
    uint16_t portno;
    struct sockaddr_in server_addr;
    struct hostent *server;

    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        printf("Params error.\nExample:client-win ""server_ip"" ""server_port""\n\n");
        exit(0);
    }

    portno = (uint16_t) atoi(argv[2]);

    csocket = socket(AF_INET, SOCK_STREAM, 0);

    if(csocket < 0){
        perror("Error opening socket.\n");
        exit(1);
    }

    server = gethostbyname(argv[1]);

    if (server == NULL) {
        fprintf(stderr, "Error, no such host.\n");
        exit(0);
    }

    bzero((char *) &server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    bcopy(server->h_addr, (char *) &server_addr.sin_addr.s_addr, (size_t) server->h_length);
    server_addr.sin_port = htons(portno);

    // Connect to remote server
    if (connect(csocket , (struct sockaddr *)&server_addr , sizeof(server_addr)) < 0)
    {
        printf("Connection error.\n");
        return 10;
    }

    printf("Enter command: \n");
    while(1){
        char buffer[BUFLEN];
        char answer[BUFLEN];
        memset(buffer,0,strlen(buffer));
        memset(answer,0,strlen(answer));
        printf("Command: ");
        fgets(buffer, BUFLEN, stdin);
        buffer[strlen(buffer) - 1] = '\0';
        char *tmp = buffer;
        char *com = strtok_r(tmp, " ", &tmp);
        char *theme = strtok_r(tmp, " ", &tmp);
        char *alt = strtok_r(tmp, " ", &tmp);
        char *votes = strtok_r(tmp, " ", &tmp);
        char *trash = strtok_r(tmp, " ", &tmp);
        char *msg = "";
        int key = decoder(com);
        switch(key){
            case HELP:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case NEW:  {
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case ADD: {
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case REMOVE:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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

                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case LIST:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case CHECK:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case CHANGE:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);

                break;
            }
            case VOTE:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
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
                msg = concat(msg, votes);
                if( trash != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
                }
                int l = readn(csocket, answer);
                if ( l < 0 ){
                    printf("Error reading from socket.\n");
                }
                printf(answer);
                break;
            }
            case DISCONNECT:{
                char msg_key[2];
                snprintf(msg_key, sizeof(msg_key),"%d",key);
                msg = msg_key;
                if( theme != NULL ){
                    printf("Too much arguments. Try again.\n");
                    break;
                }
                int n = sendmsg_to(csocket, msg);
                if( n < 0 ){
                    perror("Error writing to socket.\n");
                    return 20;
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
        printf("-------------------------------------------------------------------------------\n");
    }
    return 1;
}
