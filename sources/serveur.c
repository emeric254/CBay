#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>

#ifdef WIN32
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define perror(x) printf("%s : code d'erreur : %d\n", (x), WSAGetLastError())
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

#include <errno.h>

#include "defines.h"
#include "serveur.h"


/* Variables cachees */

/* le socket d'ecoute */
int socketEcoute;
/* longueur de l'adresse */
socklen_t longeurAdr;
/* le socket de service */
int socketService;
/* le tampon de reception */
char tamponClient[LONGUEUR_TAMPON];
int debutTampon;
int finTampon;
int finConnexion = 0;

/* Initialisation.
 * Creation du serveur.
 */
int Initialisation() {
    return InitialisationAvecService("13214");
}

/* Initialisation.
 * Creation du serveur en precisant le service ou numero de port.
 * renvoie 1 si ca c'est bien passe 0 sinon
 */
int InitialisationAvecService(char *service) {
    int n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    #ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
    {
        printf("WSAStartup() n'a pas fonctionne, erreur : %d\n", WSAGetLastError()) ;
        WSACleanup();
        exit(1);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    #else
    bzero(&hints, sizeof(struct addrinfo));
    #endif

    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ( (n = getaddrinfo(NULL, service, &hints, &res)) != 0)  {
            printf("Initialisation, erreur de getaddrinfo : %s", gai_strerror(n));
            return 0;
    }
    ressave = res;

    do {
        socketEcoute = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (socketEcoute < 0)
            continue;       /* error, try next one */

        setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
#ifdef BSD
        setsockopt(socketEcoute, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
#endif
        if (bind(socketEcoute, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* success */

        close(socketEcoute);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("Initialisation, erreur de bind.");
            return 0;
    }

    /* conserve la longueur de l'addresse */
    longeurAdr = res->ai_addrlen;

    freeaddrinfo(ressave);
    /* attends au max 4 clients */
    listen(socketEcoute, 4);
    printf("Creation du serveur reussie. (port : %s)\n",service);

    return 1;
}

/* Attends qu'un client se connecte */
int AttenteClient() {
    struct sockaddr *clientAddr;
    char machine[NI_MAXHOST];

    clientAddr = (struct sockaddr*) malloc(longeurAdr);
    socketService = accept(socketEcoute, clientAddr, &longeurAdr);
    if (socketService == -1) {
        perror("AttenteClient, erreur de accept.");
        return 0;
    }
    if(getnameinfo(clientAddr, longeurAdr, machine, NI_MAXHOST, NULL, 0, 0) == 0) {
        printf("Client sur la machine d'adresse %s connecte.\n", machine);
    } else {
        printf("Client anonyme connecte.\n");
    }
    free(clientAddr);
    /*
     * Reinit buffer
     */
    debutTampon = 0;
    finTampon = 0;
    finConnexion = FALSE;

    return 1;
}

/* Recoit un message envoye par le serveur */
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
            //fprintf(stderr, "Boucle recherche char : %c(%x), index %d debut tampon %d.\n",
            //      tamponClient[debutTampon], tamponClient[debutTampon], index, debutTampon);
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
            //fprintf(stderr, "trouve\n");
#ifdef WIN32
            return _strdup(message);
#else
            return strdup(message);
#endif
        } else {
            /* il faut en lire plus */
            debutTampon = 0;
            //fprintf(stderr, "recv\n");
            retour = recv(socketService, tamponClient, LONGUEUR_TAMPON, 0);
            //fprintf(stderr, "retour : %d\n", retour);
            if (retour < 0) {
                perror("Reception, erreur de recv.");
                return NULL;
            } else if(retour == 0) {
                fprintf(stderr, "Reception, le client a ferme la connexion.\n");
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

/* Envoie un message au client.
 * Attention, le message doit etre termine par \n
 */
int Emission(char *message) {
    int taille;
    if(strstr(message, "\n") == NULL) {
        fprintf(stderr, "Emission, Le message n'est pas termine par \\n.\n");
    }
    taille = strlen(message);
    if (send(socketService, message, taille,0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
    }
//  printf("Emission de %d caracteres.\n", taille+1);
    return 1;
}

/* Recoit des donnees envoyees par le client */
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
        retour = recv(socketService, donnees + dejaRecu, tailleMax - dejaRecu, 0);
        if(retour < 0) {
            perror("ReceptionBinaire, erreur de recv.");
            return -1;
        } else if(retour == 0) {
            fprintf(stderr, "ReceptionBinaire, le client a ferme la connexion.\n");
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

/* Envoie des donnees au client en precisant leur taille */
int EmissionBinaire(char *donnees, size_t taille) {
    int retour = 0;
    retour = send(socketService, donnees, taille, 0);
    if(retour == -1) {
        perror("Emission, probleme lors du send.");
        return -1;
    } else {
        return retour;
    }
}

/* Ferme la connexion avec le client */
void TerminaisonClient() {
    close(socketService);
}

/* Arrete le serveur */
void Terminaison() {
    close(socketEcoute);
}

// ------------------------------------------------------------

/* ex 8.a
 * Utilisation de pointeur de pointeur puisque l'on s'amuse avec le pointeur ;)
*/
int extraitFichier(char *requete, char **nomFichier, size_t *maxNomFichier){
    free(*nomFichier); //
    if(sscanf(requete,"GET /%ms HTTP",nomFichier)!=1) // alloue automatiquement
    {
#ifdef DEBUG
    fprintf(stderr,"erreur requete invalide : extraitFichier(%s)\n",requete);
#endif
        return 0;
    }
    *maxNomFichier = strlen(*nomFichier); // longeur du nom du fichier
    return 1;
}

/* ex 8.b
*/
size_t longueur_fichier(char *nomFichier){
  int longeur = -1;
  FILE * fichier = fopen(nomFichier,"r");
  if (fichier!=NULL)
  {
      fseek(fichier,0,SEEK_END); // on se place a la fin du fichier
      longeur = ftell(fichier); // on regarde ou on est pour connaitre la taille du fichier
      fclose(fichier);
  }
#ifdef DEBUG
    fprintf(stderr,"fichier inexistant : longueur_fichier(%s)\n",nomFichier);
#endif
  return longeur; // -1 si inexistant, 0 si vide, sinon X
}

/* ex 8.c
*/
int envoyerContenuFichierTexte(char *nomFichier){
    FILE * fichier = NULL;
    int retour = 0;
    int longeur = longueur_fichier(nomFichier);
    char data[longeur]; // au pire c'est un fichier en 1 seule ligne donc de la longeur du fichier !

    fichier = fopen(nomFichier,"r");

    if(fichier == NULL)
    {
#ifdef DEBUG
    fprintf(stderr,"erreur ouverture fichier : envoiContenuFichierTexte(%s)\n",nomFichier);
#endif
        return 0;
    }

    while(fgets(data, longeur, fichier)!=NULL) // lire une ligne
        if(!EmissionBinaire(data,strlen(data))) // l'envoyer
        {
#ifdef DEBUG
    fprintf(stderr,"erreur envoi : envoiContenuFichierTexte(%s)\n",nomFichier);
#endif
            retour ++;
        }

    fclose(fichier);// fermeture fichier

    return !retour;
}

/* ex 8.d
*/
int envoyerReponse200HTML(char *nomFichier){
    int retour=0;
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierTexte(nomFichier);
#ifdef DEBUG
    if(!retour)
        fprintf(stderr,"erreur envoi : envoyerReponse200HTML(%s)\n",nomFichier);
#endif
    return retour;
}

/* ex 8.e
*/
int envoyerReponse404(){
    int retour=0;
    char nomFichier[]="404.html";
#ifdef DEBUG
    fprintf(stderr,"erreur 404\n");
#endif
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 404 Not Found\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierTexte(nomFichier);
#ifdef DEBUG
    if (!retour)
        fprintf(stderr,"erreur envoi : envoyerReponse404(%s)\n",nomFichier);
#endif
    return retour;
}

/* ex 8.f
*/
int envoyerReponse500(){
    int retour=0;
    char nomFichier[]="500.html";
#ifdef DEBUG
    fprintf(stderr,"erreur 500\n");
#endif
    Emission("\n\n");
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 500 Internal Server Error\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierTexte(nomFichier);
#ifdef DEBUG
    if(!retour)
        fprintf(stderr,"erreur envoi : envoyerReponse500(%s)\n",nomFichier);
#endif
    return retour;
}

/* ex 11.a
*/
int envoyerContenuFichierBinaire(char *nomFichier){
    FILE * fichier = NULL;
    int retour = 0;
    int longeur = longueur_fichier(nomFichier);
    int taille_lue = 0;
    char ptr[LONGUEUR_TAMPON];

    fichier = fopen(nomFichier,"r");

    if(fichier == NULL)
    {
#ifdef DEBUG
    fprintf(stderr,"erreur ouverture fichier : envoyerContenuFichierBinaire(%s)\n",nomFichier);
#endif
        return 0;
    }

    do{
        taille_lue = fread(ptr, 1, LONGUEUR_TAMPON, fichier);
        if(taille_lue>0)
            if(!EmissionBinaire(ptr,LONGUEUR_TAMPON))
            {
#ifdef DEBUG
    fprintf(stderr,"erreur envoi : envoyerContenuFichierBinaire(%s)\n",nomFichier);
#endif
                retour ++;
            }
    }while(taille_lue>0);

    fclose(fichier);// fermeture fichier

    return !retour;
}

/* ex 11.b
*/
int envoyerReponse200JPG(char *nomFichier){
    int retour=0;
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 200 OK\nContent-Type: text/jpg; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierBinaire(nomFichier);
    return retour;
}

/* ex 13.a
*/
int envoyerReponse200ICO(char *nomFichier){
    int retour=0;
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 200 OK\nContent-Type: image/vnd.microsoft.ico; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierBinaire(nomFichier);
    return retour;
}

// autres :

// verifie l'extension/le suffixe d'un fichier
int testExtension(char *nomFichier, char *extension){
    // ternaire qui renvoi 1 si extension en fin de nomFichier == extension sinon 0

    // ca evite de calculer plusieurs fois les longeurs des chaines :
    int len_fic = strlen(nomFichier);
    int len_ext = strlen(extension);

    return ( len_fic > ( len_ext + 1 ) ) ? ( ! strcmp( &nomFichier[len_fic - len_ext], extension ) ) : 0;
}

int envoyerReponse400(){
    int retour=0;
    char nomFichier[]="400.html";
#ifdef DEBUG
    fprintf(stderr,"erreur 400\n");
#endif
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 400 Bad Request\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierTexte(nomFichier);
#ifdef DEBUG
    if(!retour)
        fprintf(stderr,"erreur envoi : envoyerReponse400(%s)\n",nomFichier);
#endif
    return retour;
}

int envoyerReponse403(){
    int retour=0;
    char nomFichier[]="403.html";
#ifdef DEBUG
    fprintf(stderr,"erreur 403\n");
#endif
    char content [LONGUEUR_TAMPON];
    sprintf(content,"HTTP/1.1 403 Forbidden\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",longueur_fichier(nomFichier));
    if(retour = Emission(content))
        retour = envoyerContenuFichierTexte(nomFichier);
#ifdef DEBUG
    if(!retour)
        fprintf(stderr,"erreur envoi : envoyerReponse403(%s)\n",nomFichier);
#endif
    return retour;
}
