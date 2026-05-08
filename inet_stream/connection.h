#ifndef _CONNECTION_H_
#define _CONNECTION_H_

#include "stdio.h"
#include "stdlib.h"

#define BUFFER_SIZE             256U
#define LISTEN_BACKLOG          20U

#define error_handle(msg)       \
    do {                        \
        perror(msg);            \
        exit(EXIT_FAILURE);     \
    } while(0)

#endif // _CONNECTION_H_