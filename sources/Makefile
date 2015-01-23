CC=gcc
CFLAGS=-W -Wall

CLIENTSOURCES=structures.o interfaceClient.o client.o mainClient.o
SERVERSOURCES=structures.o server.o mainServer.o
EXEC=client server

CLIENTOBJECT=$(CLIENTSOURCES:.c=.o)
SERVEROBJECT=$(SERVERSOURCES:.c=.o)

all: $(CLIENTSOURCES) $(SERVERSOURCES) $(EXEC)

client: $(CLIENTOBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

server: $(SERVEROBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
