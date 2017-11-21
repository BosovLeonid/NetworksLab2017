#include <client.h>
// Отправка сообщения серверу
int sendmsg_to(int socket, char *msg){
    int n = write(socket, msg, strlen(msg));
    if (n < 0) {
        perror("Error writing to socket");
        return 0;
    }
    return n;
}
