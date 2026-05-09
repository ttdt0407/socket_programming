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
    char temp_buff[BUFFER_SIZE];
    int serfd, port_num, num_read, num_write, status;
    socklen_t recv_len;
    struct sockaddr_in ser_addr, cli_addr;

    recv_len = sizeof(struct sockaddr_in);
    memset(&ser_addr, 0, recv_len);
    memset(&cli_addr, 0, recv_len);

    serfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (serfd < 0) {
        perror("socket()");
        close(serfd);
        return serfd;
    }

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <port>\n", argv[0]);
        return 1;
    }

    port_num = atoi(argv[1]);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons((uint16_t)port_num);
    ser_addr.sin_addr.s_addr = INADDR_ANY;

    status = bind(serfd, (struct sockaddr*)&ser_addr, sizeof(struct sockaddr_in));
    if (status < 0) {
        perror("bind()");
        close(serfd);
        return status;
    }
    printf("Host is ready\n");

    num_read = recvfrom(serfd, recv_buff, BUFFER_SIZE, 0, (struct sockaddr *)&cli_addr, &recv_len);
    if (num_read <= 0) {
        perror("recvfrom()");
        close(serfd);
        return num_read;
    }

    if (num_read < BUFFER_SIZE)
        recv_buff[num_read] = '\0';
    else
        recv_buff[BUFFER_SIZE - 1] = '\0';

    inet_ntop(AF_INET, &cli_addr.sin_addr, temp_buff, BUFFER_SIZE);

    printf("Received %zu byte with: %s from IP: %s\n", strlen(recv_buff), recv_buff, temp_buff);

    strcpy(send_buff, "Host is received your message");

    num_write = sendto(serfd, send_buff, strlen(send_buff), 0, (struct sockaddr *)&cli_addr, recv_len);
        if (num_write <= 0) {
        perror("sendto()");
        close(serfd);
        return 1;
    }

    close(serfd);

    return 0;
}