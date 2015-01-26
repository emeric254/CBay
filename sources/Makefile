# compiler
CC=gcc
# compiler argument(s)
CFLAGS=-W -Wall

# necessary file for client (in dependency order)
CLIENTSOURCES=structures.c interfaceClient.c client.c mainClient.c
#  necessary file for server (in dependency order)
SERVERSOURCES=structures.c serveur.c mainServeur.c
# both executables
EXEC=client serveur

# produces list of '.o' then all '.c'
CLIENTOBJECT=$(CLIENTSOURCES:.c=.o)
SERVEROBJECT=$(SERVERSOURCES:.c=.o)

#
all: $(EXEC)

# the client
client: $(CLIENTOBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

# the server
serveur: $(SERVEROBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

# create each '.o' from it's '.c'
%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

# cleanse
clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
