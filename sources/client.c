
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#ifdef WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #define perror(x) fprintf(ERROROUTPUT, "%d : %s\n", WSAGetLastError(), (x))
    #define close closesocket
    #define socklen_t int
#else
    #include <unistd.h>
    #include <netdb.h>
    #include <sys/socket.h>
    #include <sys/select.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <strings.h>
#endif


#include "defines.h"
#include "client.h"


/* Variable(s) privée(s) */

/* le socket client */
int socketClient;

/* le tampon de reception */
char tamponClient[LONGUEUR_TAMPON];
int debutTampon;
int finTampon;
int finConnexion = FALSE;


/* Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 */
int Initialisation(char *machine) {
    int n;
    struct addrinfo hints, *res, *ressave;
    char *service = PORT_SERVEUR;

#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
    {
        fprintf(ERROROUTPUT,"WSAStartup() n'a pas fonctionne, erreur : %d\n", WSAGetLastError()) ;
        WSACleanup();
        exit(1);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
#else
    bzero(&hints, sizeof(struct addrinfo));
#endif
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(machine, service, &hints, &res)) )
    {
            fprintf(ERROROUTPUT, "Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
            return 0;
    }
    ressave = res;

    do {
        socketClient = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socketClient < 0)
            continue;   /* ignore this one */

        if ( ! connect(socketClient, res->ai_addr, res->ai_addrlen))
            break;      /* success */

        close(socketClient);    /* ignore this one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("Initialisation, erreur de connect.");
            return 0;
    }

    freeaddrinfo(ressave);

    finConnexion = FALSE;

    printf("Connexion avec le serveur reussie.\n");

    return 1;
}

/* Recoit un message envoye par le serveur.
 */
char *Reception() {
    char message[LONGUEUR_TAMPON];
    int index = 0;
    int fini = FALSE;
    int retour = 0;
    int trouve = FALSE;

    if(finConnexion) {
        return NULL;
    }

    while(!fini) {
        /* on cherche dans le tampon courant */
        while((finTampon > debutTampon) && (!trouve)) {
            //fprintf(ERROROUTPUT, "Boucle recherche char : %c(%x), index %d debut tampon %d.\n",
            //                  tamponClient[debutTampon], tamponClient[debutTampon], index, debutTampon);
            if (tamponClient[debutTampon]=='\n')
                trouve = TRUE;
            else
                message[index++] = tamponClient[debutTampon++];
        }
        /* on a trouve ? */
        if (trouve) {
            message[index++] = '\n';
            message[index] = '\0';
            debutTampon++;
            fini = TRUE;
            //fprintf(ERROROUTPUT, "trouve\n");
#ifdef WIN32
            return _strdup(message);
#else
            return strdup(message);
#endif
        } else {
            /* il faut en lire plus */
            debutTampon = 0;
            //fprintf(ERROROUTPUT, "recv\n");
            retour = recv(socketClient, tamponClient, LONGUEUR_TAMPON, 0);
            //fprintf(ERROROUTPUT, "retour : %d\n", retour);
            if (retour < 0) {
                perror("Reception, erreur de recv.");
                return NULL;
            } else if(retour == 0) {
                fprintf(ERROROUTPUT, "Reception, le serveur a ferme la connexion.\n");
                finConnexion = TRUE;
                // on n'en recevra pas plus, on renvoie ce qu'on avait ou null sinon
                if(index > 0) {
                    message[index++] = '\n';
                    message[index] = '\0';
#ifdef WIN32
                    return _strdup(message);
#else
                    return strdup(message);
#endif
                } else {
                    return NULL;
                }
            } else {
                /*
                 * on a recu "retour" octets
                 */
                finTampon = retour;
            }
        }
    }
    return NULL;
}

/* Envoie un message au serveur.
 * Attention, le message doit etre termine par \n
 */
int Emission(char *message) {
    int taille;
    if(strstr(message, "\n") == NULL) {
        fprintf(ERROROUTPUT, "Emission, Le message n'est pas termine par \\n.\n");
    }
    taille = strlen(message);
    if (send(socketClient, message, taille,0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
    }
    printf("Emission de %d caracteres.\n", taille+1);
    return 1;
}

/* Recoit des donnees envoyees par le serveur.
 */
int ReceptionBinaire(char *donnees, size_t tailleMax) {
    size_t dejaRecu = 0;
    int retour = 0;
    /* on commence par recopier tout ce qui reste dans le tampon
     */
    while((finTampon > debutTampon) && (dejaRecu < tailleMax)) {
        donnees[dejaRecu] = tamponClient[debutTampon];
        dejaRecu++;
        debutTampon++;
    }
    /* si on n'est pas arrive au max
     * on essaie de recevoir plus de donnees
     */
    if(dejaRecu < tailleMax) {
        retour = recv(socketClient, donnees + dejaRecu, tailleMax - dejaRecu, 0);
        if(retour < 0) {
            perror("ReceptionBinaire, erreur de recv.");
            return -1;
        } else if(retour == 0) {
            fprintf(ERROROUTPUT, "ReceptionBinaire, le serveur a ferme la connexion.\n");
            return 0;
        } else {
            /*
             * on a recu "retour" octets en plus
             */
            return dejaRecu + retour;
        }
    } else {
        return dejaRecu;
    }
}

/* Envoie des donnees au serveur en precisant leur taille.
 */
int EmissionBinaire(char *donnees, size_t taille) {
    int retour = 0;
    retour = send(socketClient, donnees, taille, 0);
    if(retour == -1) {
        perror("Emission, probleme lors du send.");
        return -1;
    } else {
        return retour;
    }
}


/* Ferme la connexion.
 */
void Terminaison() {
    close(socketClient);
}
