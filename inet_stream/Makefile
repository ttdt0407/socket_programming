CC = gcc
CFLAGS = -Wall -Wextra -g

all: stream_server stream_client

stream_server: stream_server.o
	$(CC) $(CFLAGS) -o $@ $^

stream_client: stream_client.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -rf stream_server stream_client *.o
