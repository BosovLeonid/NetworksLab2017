#include <client.h>
// Отправка сообщения серверу
int sendmsg(int socket, char *msg){
    int n = send(socket, msg, strlen(msg), 0);
    if (n < 0) {
        perror("Error writing to socket");
        return 0;
    }
    return n;
}
