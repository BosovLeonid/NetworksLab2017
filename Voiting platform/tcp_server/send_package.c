#include <server.h>
// Отправка пакета клиенту
// Пакет - количество байт, которые надо принять,
// и ответ сервера на команду
const int MAX_LEN_OF_MSG = 2048;
int send_package(int socket){
    int bytes_to_send = htonl(strnlen(answer, MAX_LEN_OF_MSG));
    int n = send(socket, &bytes_to_send, sizeof(bytes_to_send), 0);
    if (n < 0) {
        perror("Error writing to socket");
        printf("\n");
        return 0;
    }
    printf("Sending %d bytes to %d socket.\n", htonl(bytes_to_send), socket);
    n = send(socket, answer, strnlen(answer, MAX_LEN_OF_MSG), 0);
    if (n < 0) {
        perror("Error writing to socket");
        printf("\n");
        return 0;
    }
    return n;
}
