all: dgram_server dgram_client

server: dgram_server.o
	gcc -o $@ $<

client: dgram_client.o
	gcc -o $@ $<

server.o: dgram_server.c
	gcc -c $<

client.o: dgram_client.c
	gcc -c $<

clean:
	rm -rf dgram_server dgram_client *.o
