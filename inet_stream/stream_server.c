#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "connection.h"

void chat(int new_socket) {
    char recv_buff[BUFFER_SIZE];
    char send_buff[BUFFER_SIZE];
    int num_read;
    int num_write;

    while(1) {
        memset(recv_buff, 0, BUFFER_SIZE);
        memset(send_buff, 0, BUFFER_SIZE);

        num_read = read(new_socket, recv_buff, BUFFER_SIZE - 1);
        if (num_read <= 0) {
            printf("Client closed connect\n");
            break;
        }
        recv_buff[num_read] = '\0';

        if (strncmp("exit", recv_buff, 4) == 0) {
            printf("Client request exit !\n");
            break;
        }
        printf("Received: %s", recv_buff);

        printf("Response to client: ");
        if (fgets(send_buff, BUFFER_SIZE, stdin) == NULL) {
            break;
        };

        num_write = write(new_socket, send_buff, strlen(send_buff));
        if (num_write <= 0) {
            error_handle("write");
        }

        if (strncmp("exit", send_buff, 4) == 0) {
            printf("stop !\n");
            break;
        }
    }
    close(new_socket);
}

int main(int argc, char *argv[]) {

    struct sockaddr_in server_addr;
    struct sockaddr_in peer_addr;
    socklen_t peer_len;
    int sfd;
    int port_num;
    int cfd;
    int opt = 1;

    if (argc < 2) {
        printf("ERROR: no port provied !\ncommand: ./stream_server <port_num>\n");
        exit(EXIT_FAILURE);
    }
    port_num = atoi(argv[1]);

    sfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sfd == -1) {
        error_handle("socket");
    }

    if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        error_handle("setsockopt");
    };

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_num);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        error_handle("bind");
    }

    if (listen(sfd, LISTEN_BACKLOG) == -1) {
        error_handle("listen");
    }

    while(1) {
        printf("Server is listening at port %d\n ... \n", port_num);
        peer_len = sizeof(peer_addr);
        cfd = accept(sfd, (struct sockaddr *)&peer_addr, &peer_len);
        if (cfd == -1) {
            error_handle("accept");
        }
        chat(cfd);
    }
    close(sfd);

    return 0;
}
