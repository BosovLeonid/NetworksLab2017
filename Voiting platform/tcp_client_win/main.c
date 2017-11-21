#include <client.h>
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET csocket;
    struct sockaddr_in server;

    setlocale(LC_ALL, "Rus");

    if (argc < 3) {
        printf("Params ERROR.\nExample:client-win ""server_ip"" ""server_port""\n\n");
        exit(0);
    }

    if (WSAStartup(0x0202,&wsa) != 0)
    {
        printf("Failed. Error Code : %d\n",WSAGetLastError());
        return 1;
    }
    //Create a socket
    if((csocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n" , WSAGetLastError());
    }

    server.sin_addr.s_addr = inet_addr(argv[1]);
    server.sin_family = AF_INET;
    server.sin_port = htons( (UINT16)atoi(argv[2]));

    // Connect to remote server
    if (connect(csocket , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        printf("Connection error.\n");
        return 1;
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
                }
                printf(answer);
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
                system("pause");
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
