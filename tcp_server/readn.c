#include <server.h>
int readn(int *socket,char* output){
    char buffer[256];
    int length = 0;
    *output = (char*)malloc(length);
    memset(output,0,strlen(output));
    while( 1 ){
        memset(buffer,0,strlen(buffer));
        int n = recv(socket, buffer, 255,0);
        if (n < 0) return -1;
        else
        {
            if(n < 255){
                length += n;
                buffer[n] = '\0';
                strcpy(output,buffer);
                return length;
            }
            else{
                length += n;
            }
        }
    }
    return -1;
}
