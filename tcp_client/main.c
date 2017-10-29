#include <client.h>
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET csocket;
    struct sockaddr_in server;

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
        char buffer[256];
        memset(buffer,0,strlen(buffer));
        printf("Command: ");
        scanf("%[^\n]",buffer);
        char *tmp = buffer;
        char *tmp1 = strtok(tmp, " ");
        switch(decoder(tmp1)){
            case NEW:  {
                break;
            }
            case ADD: {
                break;
            }
            case REMOVE:{

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
                break;
            }
            case HELP:{
                break;
            }
            default:    {
                printf("Command %d not found\n",tmp1);
                printf("Type ""help"" to get list of avalible commands.\n");
                break;
            }
            memset(buffer,0,strlen(buffer));
        }
    }
    return 1;
}
