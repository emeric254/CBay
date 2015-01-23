CC=gcc
CFLAGS=-W -Wall

#
CLIENTSOURCES=structures.c interfaceClient.c client.c mainClient.c
#
SERVERSOURCES=structures.c server.c mainServer.c
EXEC=client server

CLIENTOBJECT=$(CLIENTSOURCES:.c=.o)
SERVEROBJECT=$(SERVERSOURCES:.c=.o)

all: $(EXEC)

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
