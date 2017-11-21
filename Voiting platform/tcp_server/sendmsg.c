#include <server.h>
// Отправка сообщения клиенту
int sendmsg(int socket){
    int n = send(socket, answer, strlen(answer), 0);
    if (n < 0) {
        perror("Error writing to socket");
        return 0;
    }
    return n;
}
