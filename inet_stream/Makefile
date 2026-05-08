all: client server

client: stream_client.c
	gcc -o client stream_client.c

server: stream_server.c
	gcc -o server stream_server.c

clean:
	rm -rf client server *.o

.PHONY: all client server clean
