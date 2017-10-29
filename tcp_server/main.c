#include <server.h>

int main(int argc, char *argv[])
{
    WSADATA wsa;
    SOCKET serverSocket, accSocket;
    struct sockaddr_in server,client;
    //Указываем рабочий каталог
    getcwd(CURRENT_DIR, 50);
    /*
    Тест работоспособности функций
    add_theme("first");
    printf("%s\n", answer);
    add_theme("second");
    printf("%s\n", answer);
    add_theme("third");
    printf("%s\n", answer);
    add_alt("first","1");
    printf("%s\n", answer);
    add_alt("third","11");
    printf("%s\n", answer);
    add_alt("first","1");
    printf("%s\n", answer);
    add_alt("second","ffew");
    printf("%s\n", answer);
    add_alt("second","124");
    printf("%s\n", answer);
    remove_theme("second");
    printf("%s\n", answer);*/

    if (WSAStartup(0x0202,&wsa) != 0)
    {
        printf("Failed. Error Code : %d", WSAGetLastError());
        return 1;
    }
    // Create a socket
    if((serverSocket = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }

    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons( (UINT16)atoi(argv[1]) );

    //Bind
    if( bind(serverSocket ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }

    //Listen to incoming connections
    listen(serverSocket , 5);
    printf("Waiting for incoming connections\n\n");
    int c = sizeof(struct sockaddr_in);

    pthread_t thread_id;

    while( (accSocket = accept(serverSocket, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        args.ip = inet_ntoa(client.sin_addr);
        args.port = ntohs(client.sin_port);
        args.socket = accSocket;
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &args) < 0)
        {
            perror("Сouldn't create thread");
            return 1;
        }
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        printf("Thread created for: %s:%d\n",inet_ntoa(client.sin_addr) ,ntohs(client.sin_port));
    }

    if (accSocket < 0)
    {
        perror("accept failed");
        return 1;
    }

    closesocket(serverSocket);
    WSACleanup();
}


