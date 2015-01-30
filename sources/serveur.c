#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <errno.h>

#ifdef WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
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
#include "serveur.h"


int listenSocket;
socklen_t adressLength;
int mainSocket;
char clientBuffer[BUFFER_LENGTH];
int bufferStart;
int bufferEnd;
int connectEnd = FALSE;


/* Init.
 * 
 */
int Init(char *port) {
    int n;
    const int on = 1;
    struct addrinfo hints, *res, *ressave;

    #ifdef WIN32
        WSADATA wsaData;
        if (WSAStartup(0x202,&wsaData) == SOCKET_ERROR)
        {
            fprintf(ERROROUTPUT, "WSAStartup() failed, error : %d\n", WSAGetLastError()) ;
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

    if ( (n = getaddrinfo(NULL, port, &hints, &res)) != 0)  {
            fprintf(ERROROUTPUT, "getaddrinfo() failed, error : %s", gai_strerror(n));
            return 0;
    }
    ressave = res;

    do {
        listenSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (listenSocket < 0)
            continue;       /* error, try next one */

        setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&on, sizeof(on));
#ifdef BSD
        setsockopt(listenSocket, SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on));
#endif
        if (bind(listenSocket, res->ai_addr, res->ai_addrlen) == 0)
            break;          /* SUCESSs */

        close(listenSocket);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("bind error");
            return 0;
    }

    adressLength = res->ai_addrlen;

    freeaddrinfo(ressave);
    listen(listenSocket, 4);
    printf("Init sucess\n");

    return 1;
}


/*
 *
*/
int connectWait() {
    struct sockaddr *clientAddr;
    char machine[NI_MAXHOST];

    clientAddr = (struct sockaddr*) malloc(adressLength);
    mainSocket = accept(listenSocket, clientAddr, &adressLength);
    if (mainSocket == -1) {
        perror("AttenteClient, erreur de accept.");
        return 0;
    }
    if(getnameinfo(clientAddr, adressLength, machine, NI_MAXHOST, NULL, 0, 0) == 0) {
        printf("Client sur la machine d'adresse %s connecte.\n", machine);
    } else {
        printf("Client anonyme connecte.\n");
    }
    free(clientAddr);
    /*
     * Reinit buffer
     */
    bufferStart = 0;
    bufferEnd = 0;
    connectEnd = FALSE;

    return 1;
}


/* Recoit un message envoye par le serveur */
char *Reception() {
    char message[BUFFER_LENGTH];
    int index = 0;
    int fini = FALSE;
    int retour = 0;
    int trouve = FALSE;

    if(connectEnd) {
        return NULL;
    }

    while(!fini) {
        /* on cherche dans le tampon courant */
        while((bufferEnd > bufferStart) && (!trouve)) {
            //fprintf(ERROROUTPUT, "Boucle recherche char : %c(%x), index %d debut tampon %d.\n",
            //      clientBuffer[bufferStart], clientBuffer[bufferStart], index, bufferStart);
            if (clientBuffer[bufferStart]=='\n')
                trouve = TRUE;
            else
                message[index++] = clientBuffer[bufferStart++];
        }
        /* on a trouve ? */
        if (trouve) {
            message[index++] = '\n';
            message[index] = '\0';
            bufferStart++;
            fini = TRUE;
            //fprintf(ERROROUTPUT, "trouve\n");
#ifdef WIN32
            return _strdup(message);
#else
            return strdup(message);
#endif
        } else {
            /* il faut en lire plus */
            bufferStart = 0;
            //fprintf(ERROROUTPUT, "recv\n");
            retour = recv(mainSocket, clientBuffer, BUFFER_LENGTH, 0);
            //fprintf(ERROROUTPUT, "retour : %d\n", retour);
            if (retour < 0) {
                perror("Reception, erreur de recv.");
                return NULL;
            } else if(retour == 0) {
                fprintf(ERROROUTPUT, "Reception, le client a ferme la connexion.\n");
                connectEnd = TRUE;
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
                bufferEnd = retour;
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
        fprintf(ERROROUTPUT, "Emission, Le message n'est pas termine par \\n.\n");
    }
    taille = strlen(message);
    if (send(mainSocket, message, taille,0) == -1) {
        perror("Emission, probleme lors du send.");
        return 0;
    }
//  printf("Emission de %d caracteres.\n", taille+1);
    return 1;
}

/* Recoit des donnees envoyees par le client */
int receiveBinary(char *donnees, size_t tailleMax) {
    size_t dejaRecu = 0;
    int retour = 0;
    /* on commence par recopier tout ce qui reste dans le tampon
     */
    while((bufferEnd > bufferStart) && (dejaRecu < tailleMax)) {
        donnees[dejaRecu] = clientBuffer[bufferStart];
        dejaRecu++;
        bufferStart++;
    }
    /* si on n'est pas arrive au max
     * on essaie de recevoir plus de donnees
     */
    if(dejaRecu < tailleMax) {
        retour = recv(mainSocket, donnees + dejaRecu, tailleMax - dejaRecu, 0);
        if(retour < 0) {
            perror("receiveBinary, erreur de recv.");
            return -1;
        } else if(retour == 0) {
            fprintf(ERROROUTPUT, "receiveBinary, le client a ferme la connexion.\n");
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
int sendBinary(char *donnees, size_t taille) {
    int retour = 0;
    retour = send(mainSocket, donnees, taille, 0);
    if(retour == -1) {
        perror("Emission, probleme lors du send.");
        return -1;
    } else {
        return retour;
    }
}

/* Ferme la connexion avec le client */
void TerminaisonClient() {
    close(mainSocket);
}

/* Arrete le serveur */
void Terminaison() {
    close(listenSocket);
}

// ------------------------------------------------------------


/*
*/
size_t file_length(char *filename){
    int length = -1;
    FILE * file = fopen(filename,"r");
    if (file!=NULL)
    {
        fseek(file,0,SEEK_END);
        length = ftell(file);
        fclose(file);
    }
    fprintf(ERROROUTPUT,"error unknown file : (%s)\n",filename);
    return length; // -1 if unknown file, 0 if empty, otherwise it return the file length
}


/*
*/
int sendStatusLine(int statusCode){
    int retour=0;
    char statusLine[STATUS_LINE_LENGTH+1];
    switch(statusCode)
    {
        case STATUS_CODE_OK:
            strcpy(statusLine, "STATUS_CODE_OK");
            break;
        case STATUS_CODE_CREATED:
            strcpy(statusLine, "STATUS_CODE_CREATED");
            break;
        case STATUS_CODE_BAD_REQUEST:
            strcpy(statusLine, "STATUS_CODE_BAD_REQUEST");
            break;
        case STATUS_CODE_NOT_CREATED:
            strcpy(statusLine, "STATUS_CODE_NOT_CREATED");
            break;
        case STATUS_CODE_CONFLICT:
            strcpy(statusLine, "STATUS_CODE_CONFLICT");
            break;
        case STATUS_CODE_FORBIDDEN:
            strcpy(statusLine, "STATUS_CODE_FORBIDDEN");
            break;
        default:    // equivalent to : case STATUS_CODE_INTERNAL_SERVER_ERROR:
            strcpy(statusLine, "STATUS_CODE_INTERNAL_SERVER_ERROR");
            break;
    }
    statusLine[2] = ' ';
    switch(statusCode)
    {
        case STATUS_CODE_OK:
            strcpy(&statusLine[3], REASON_PHRASE_OK);
            break;
        case STATUS_CODE_CREATED:
            strcpy(&statusLine[3], REASON_PHRASE_CREATED);
            break;
        case STATUS_CODE_BAD_REQUEST:
            strcpy(&statusLine[3], REASON_PHRASE_BAD_REQUEST);
            break;
        case STATUS_CODE_NOT_CREATED:
            strcpy(&statusLine[3], REASON_PHRASE_NOT_CREATED);
            break;
        case STATUS_CODE_CONFLICT:
            strcpy(&statusLine[3], REASON_PHRASE_CONFLICT);
            break;
        case STATUS_CODE_FORBIDDEN:
            strcpy(&statusLine[3], REASON_PHRASE_FORBIDDEN);
            break;
        default:    // equivalent to : case STATUS_CODE_INTERNAL_SERVER_ERROR:
            strcpy(&statusLine[3], REASON_PHRASE_INTERNAL_SERVER_ERROR);
            break;
    }
    statusLine[15] = '\n';
    statusLine[16] = '\0';
    return retour;
}


/*
*/
int sendHeaderField(){
    int retour=0;
    char headerField [RESPONSE_HEADER_LENGTH+1];
    strcpy(headerField,RESPONSE_HEADER_FIELDNAME_CONTENT_LENGTH);
    // ici mettre le {Content-length}
    headerField[31] = ';';
    strcpy(&headerField[32],RESPONSE_HEADER_FIELDNAME_CONTENT_TYPE);
    // ici mettre le {Content-type}
    headerField[62] = ';';
    headerField[63] = '\n';
    headerField[64] = '\0';
    return retour;
}


/*

int envoyerContenuFichierTexte(char *nomFichier){
    FILE * fichier = NULL;
    int retour = 0;
    int longeur = longueur_fichier(nomFichier);
    char data[longeur]; // au pire c'est un fichier en 1 seule ligne donc de la longeur du fichier !

    fichier = fopen(nomFichier,"r");

    if(fichier == NULL)
    {
        fprintf(ERROROUTPUT,"erreur ouverture fichier : envoiContenuFichierTexte(%s)\n",nomFichier);
        return 0;
    }

    while(fgets(data, longeur, fichier)!=NULL) // lire une ligne
        if(!sendBinary(data,strlen(data))) // l'envoyer
        {
            fprintf(ERROROUTPUT,"erreur envoi : envoiContenuFichierTexte(%s)\n",nomFichier);
            retour ++;
        }

    fclose(fichier);// fermeture fichier

    return !retour;
}


int envoyerReponse200HTML(char *nomFichier){
    int retour=0;
    char content [BUFFER_LENGTH];
    sprintf(content,"HTTP/1.1 200 OK\nContent-Type: text/html; charset=UTF-8\nContent-Length: %d\n\n",(int)longueur_fichier(nomFichier));
    if((retour = Emission(content)))
        retour = envoyerContenuFichierTexte(nomFichier);
    if(!retour)
        fprintf(ERROROUTPUT,"erreur envoi : envoyerReponse200HTML(%s)\n",nomFichier);
    return retour;
}


int envoyerContenuFichierBinaire(char *nomFichier){
    FILE * fichier = NULL;
    int retour = 0;
//    int longeur = longueur_fichier(nomFichier);
    int taille_lue = 0;
    char ptr[BUFFER_LENGTH];

    fichier = fopen(nomFichier,"r");

    if(fichier == NULL)
    {
        fprintf(ERROROUTPUT,"erreur ouverture fichier : envoyerContenuFichierBinaire(%s)\n",nomFichier);
        return 0;
    }

    do{
        taille_lue = fread(ptr, 1, BUFFER_LENGTH, fichier);
        if(taille_lue>0)
            if(!sendBinary(ptr,BUFFER_LENGTH))
            {
                fprintf(ERROROUTPUT,"erreur envoi : envoyerContenuFichierBinaire(%s)\n",nomFichier);
                retour ++;
            }
    }while(taille_lue>0);

    fclose(fichier);// fermeture fichier

    return !retour;
}


int envoyerReponse200JPG(char *nomFichier){
    int retour=0;
    char content [BUFFER_LENGTH];
    sprintf(content,"HTTP/1.1 200 OK\nContent-Type: text/jpg; charset=UTF-8\nContent-Length: %d\n\n",(int)longueur_fichier(nomFichier));
    if((retour = Emission(content)))
        retour = envoyerContenuFichierBinaire(nomFichier);
    return retour;
}


// verifie l'extension/le suffixe d'un fichier
int testExtension(char *nomFichier, char *extension){
    // ternaire qui renvoi 1 si extension en fin de nomFichier == extension sinon 0

    // ca evite de calculer plusieurs fois les longeurs des chaines :
    int len_fic = strlen(nomFichier);
    int len_ext = strlen(extension);

    return ( len_fic > ( len_ext + 1 ) ) ? ( ! strcmp( &nomFichier[len_fic - len_ext], extension ) ) : 0;
}

*/
