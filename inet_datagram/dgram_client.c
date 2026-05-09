#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define BUFFER_SIZE 256


int main(int argc, char *argv[])
{
    char recv_buff[BUFFER_SIZE];
    char send_buff[BUFFER_SIZE];
    int clifd, port_num, numb_read, num_write, status;
    socklen_t recv_len, send_len;
    struct sockaddr_in ser_addr;
    size_t len;

    clifd = socket(AF_INET, SOCK_DGRAM, 0);
    if (clifd < 0) {
        perror("socket()");
        close(clifd);
        return clifd;
    }

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <IP> <port>\n", argv[0]);
        return 1;
    }

    send_len = sizeof(struct sockaddr_in);
    port_num = atoi(argv[2]);

    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons((uint16_t)port_num);
    status = inet_pton(AF_INET, argv[1], (struct in_addr *)&ser_addr.sin_addr);
    if (status <= 0) {
        perror("inet_pton()");
        close(clifd);
        return status;
    }

    printf("Client is ready\n");

    fgets(send_buff, BUFFER_SIZE, stdin);

    len = strlen(send_buff);
    if (len > 0 && send_buff[len - 1] == '\n')
        send_buff[len - 1] = '\0';

    num_write = sendto(clifd, send_buff, strlen(send_buff), 0, (struct sockaddr *)&ser_addr, send_len);
        if (num_write <= 0) {
        perror("sendto()");
        close(clifd);
        return 1;
    }

    recv_len = sizeof(struct sockaddr_in);
    numb_read = recvfrom(clifd, recv_buff, BUFFER_SIZE, 0, (struct sockaddr *)&ser_addr, &recv_len);
    if (numb_read < 0) {
        perror("recvfrom()");
        close(clifd);
        return numb_read;
    }

    if (numb_read < BUFFER_SIZE) {
        recv_buff[numb_read] = '\0';
    }
    else {
        recv_buff[numb_read - 1] = '\0';
    }

    printf("Receive from server: %s\n", recv_buff);

    close(clifd);
    return 0;
}
