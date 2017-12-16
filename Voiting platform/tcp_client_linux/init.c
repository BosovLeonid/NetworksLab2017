#include <client.h>
// Установка соединения с сервером
int init(int argc, char *argv[]){
    int csocket;
    uint16_t portno;
    struct sockaddr_in server_addr;
    struct hostent *server;

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
        return -1;
    }
    return csocket;
}
