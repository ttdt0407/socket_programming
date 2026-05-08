# IPC: Socket

> IPv4, TCP


- Step 1: Compile the source code to create the object

```bash
make
```

- Step 2: Find the IP of server

```bash
ifconfig
```

- Step 3: Choose a free port, for example: 8080

- Step 4: From server side, run the program and pass the port argument:

```bash
./server 8080
```

- Step 5: From the client side, run the program, pass the IP and port of the server:

```bash
./client 192.168.100.182 8080
```
