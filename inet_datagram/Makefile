CC = gcc
CFLAGS = -Wall -Wextra -g

all: dgram_server dgram_client

dgram_server: dgram_server.o
	$(CC) $(CFLAGS) -o $@ $^

dgram_client: dgram_client.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf dgram_server dgram_client *.o
