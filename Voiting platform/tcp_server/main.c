#include <server.h>

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET serverSocket, accSocket;
    struct sockaddr_in server,client;
    setlocale(LC_ALL, "Rus");
    // Указываем рабочий каталог
    getcwd(CURRENT_DIR, 50);

    if (argc < 2) {
        printf("Params ERROR.\nExample:server_win ""server_port""\n\n");
        exit(0);
    }

    if (WSAStartup(0x0202,&wsa) != 0)
    {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return 1;
    }
    // Create a socket
    if((serverSocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d\n" , WSAGetLastError());
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( (UINT16)atoi(argv[1]) );

    // Bind
    if( bind(serverSocket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d\n" , WSAGetLastError());
    }

    // Listen to incoming connections
    listen(serverSocket , 5);
    printf("Waiting for incoming connections...\n");
    int c = sizeof(struct sockaddr_in);

    while( (accSocket = accept(serverSocket, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        args.ip = inet_ntoa(client.sin_addr);
        args.port = ntohs(client.sin_port);
        args.socket = accSocket;
        HANDLE thread = CreateThread(NULL,0,connection_handler,&args,0,NULL);
        printf("Thread created for: %s:%d, socket: %d\n",inet_ntoa(client.sin_addr) ,ntohs(client.sin_port), args.socket);
    }

    if ((INT)accSocket < 0)
    {
        perror("Accept failed.\n");
        return 1;
    }

    closesocket(serverSocket);
    WSACleanup();
}
