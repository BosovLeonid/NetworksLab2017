#include <server.h>
// Отправка ответа клиенту
int sendmsg(int *socket){
    int n = send(socket, answer, sizeof answer, 0);
    if (n < 0) {
        perror("Error writing to socket");
        return 0;
    }
    return n;
}
