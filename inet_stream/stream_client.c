#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "connection.h"

void chat(int server_fd) {
    char recv[BUFFER_SIZE];
    char send[BUFFER_SIZE];
    int num_read;
    int num_write;

    while (1) {
        memset(recv, 0, BUFFER_SIZE);
        memset(send, 0, BUFFER_SIZE);

        printf("Send to the server: ");
        fgets(send, BUFFER_SIZE, stdin);
        num_write = write(server_fd, (char *)send, strlen(send));
        if (num_write <= 0) {
            error_handle("write");
        }
        if (strncmp("exit", send, 4) == 0) {
            printf("exit !\n");
            break;
        }

        num_read = read(server_fd, (char *)recv, BUFFER_SIZE - 1);
        if (num_read <= 0) {
            printf("Server disconnected\n");
            break;
        }
        recv[num_read] = '\0';
        printf("Received from server: %s", recv);

        if (strncmp("exit", recv, 4) == 0) {
            printf("exit !\n");
            break;
        }
    }
    close(server_fd);

}

int main(int argc, char *argv[]) {

    int sfd;
    int port_num;
    struct sockaddr_in server_addr;

    if (argc < 3) {
        printf("ERROR !\ncommand: ./client <server_address> <port_number>\n");
        exit(EXIT_FAILURE);
    }

    port_num = atoi(argv[2]);
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);

    if (inet_pton(AF_INET, (const char *)argv[1], &server_addr.sin_addr) == -1) {
        error_handle("inet_pton");
    }

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        error_handle("socket");
    }

    if (connect(sfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handle("connect");
    };

    chat(sfd);

    return 0;
}
