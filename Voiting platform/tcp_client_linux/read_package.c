#include <client.h>
int read_package(int socket, char *output){
    int bytes_to_read = 0;
    int n = recv(socket, &bytes_to_read, sizeof(bytes_to_read), 0);
    if (n < 0) {
        perror("Error reading from socket");
        printf("\n");
        return 0;
    }
    bytes_to_read = htonl(bytes_to_read);
    n = recv(socket, output, bytes_to_read, 0);
    if (n < 0) {
        perror("Error reading from socket");
        printf("\n");
        return 0;
    }
    return n;
}

