# compilateur
CC=gcc
# argument(s) compilateur
CFLAGS=-W -Wall

# fichiers nécessaires pour le client (dans l'ordre de dépendance)
CLIENTSOURCES=structures.c interfaceClient.c client.c mainClient.c
#  fichier nécessaires pour le serveur (dans l'ordre de dépendance)
SERVERSOURCES=structures.c serveur.c mainServeur.c
# les deux executables
EXEC=client serveur

# on produit la liste des '.o' depuis celle des '.c'
CLIENTOBJECT=$(CLIENTSOURCES:.c=.o)
SERVEROBJECT=$(SERVERSOURCES:.c=.o)

#
all: $(EXEC)

# le client
client: $(CLIENTOBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

# le serveur
server: $(SERVEROBJECT)
		$(CC) -o $@ $^ $(LDFLAGS)

# pour créer chaque '.o' depuis son '.c'
%.o: %.c
		$(CC) -o $@ -c $< $(CFLAGS)

# nettoyages
clean:
		rm -rf *.o

mrproper: clean
		rm -rf $(EXEC)
