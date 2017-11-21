#include <server.h>
int readn(int socket,char* output){
    char buffer[BUFLEN];
    int length = 0;
    *output = (char*)malloc(length);
    memset(output,0,strlen(output));
    while( 1 ){
        memset(buffer,0,strlen(buffer));
        int n = recv(socket, buffer, BUFLEN,0);
        if (n < 0) return -1;
        else
        {
            if(n < BUFLEN){
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
