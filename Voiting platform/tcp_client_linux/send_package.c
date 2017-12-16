#include <client.h>
// Отправка пакета клиенту
// Пакет - количество байт, которые надо принять,
// и ответ сервера на команду
const int MAX_LEN_OF_MSG = 2048;
int send_package(int socket, char *massage){
    int bytes_to_send = htonl(strnlen(massage, MAX_LEN_OF_MSG));
    int n = write(socket, &bytes_to_send, sizeof(bytes_to_send), 0);
    if (n < 0) {
        perror("Error writing to socket");
        printf("\n");
        return 0;
    }
    n = write(socket, massage, strnlen(massage, MAX_LEN_OF_MSG), 0);
    if (n < 0) {
        perror("Error writing to socket");
        printf("\n");
        return 0;
    }
    return n;
}
