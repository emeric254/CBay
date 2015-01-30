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
#include "client.h"


int clientSocket;
char clientBuffer[BUFFER_LENGTH];
int bufferStart;
int bufferEnd;
int connectEnd = FALSE;


/* Init.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 */
int Initialisation(char *machine) {
    int n;
    struct addrinfo hints, *res, *ressave;
    char *service = SERVER_PORT;

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
        clientSocket = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        if (clientSocket < 0)
            continue;   /* ignore this one */

        if ( ! connect(clientSocket, res->ai_addr, res->ai_addrlen))
            break;      /* SUCESSs */

        close(clientSocket);    /* ignore this one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("Initialisation, erreur de connect.");
            return 0;
    }

    freeaddrinfo(ressave);

    connectEnd = FALSE;

    printf("Connexion avec le serveur reussie.\n");

    return 1;
}


/* Recoit un message envoye par le serveur.
 */
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
            //                  clientBuffer[bufferStart], clientBuffer[bufferStart], index, bufferStart);
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
            retour = recv(clientSocket, clientBuffer, BUFFER_LENGTH, 0);
            //fprintf(ERROROUTPUT, "retour : %d\n", retour);
            if (retour < 0) {
                perror("Reception, erreur de recv.");
                return NULL;
            } else if(retour == 0) {
                fprintf(ERROROUTPUT, "Reception, le serveur a ferme la connexion.\n");
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


/* receiveBinary.
 */
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
        retour = recv(clientSocket, donnees + dejaRecu, tailleMax - dejaRecu, 0);
        if(retour < 0) {
            perror("receiveBinary error.");
            return -1;
        } else if(retour == 0) {
            fprintf(ERROROUTPUT, "receiveBinary, le serveur a ferme la connexion.\n");
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


/* sendBinary.
 */
int sendBinary(char *donnees, size_t taille) {
    int retour = 0;
    retour = send(clientSocket, donnees, taille, 0);
    if(retour == -1) {
        perror("sendBinary error.");
        return -1;
    } else {
        return retour;
    }
}


/* sendGet.
*/
int sendGet()
{
	return 0;
}


/* sendPut.
*/
int sendPut()
{
	return 0;
}


/* sendDelete.
*/
int sendDelete()
{
	return 0;
}


/* sendConnect.
*/
int sendConnect(char* login, char* password)
{
    int length;
    char msg[64+1];
    
    strcpy(msg,REQUEST_METHOD_CONNECT);
    length = strlen(REQUEST_METHOD_CONNECT);
    
    msg[length++] = ' ';
    
    strncpy(&msg[length], login, USERACCOUNT_LOGIN_LENGTH);
    length += (strlen(login) < USERACCOUNT_LOGIN_LENGTH)? strlen(login):USERACCOUNT_LOGIN_LENGTH;
    
    msg[length++] = ';';
    
    strncpy(&msg[length], password, USERACCOUNT_PASSWORD_LENGTH);
    length += (strlen(password) < USERACCOUNT_PASSWORD_LENGTH)? strlen(password):USERACCOUNT_PASSWORD_LENGTH;
    
    msg[length++] = ';';
    msg[length++] = '\n';
    msg[length] = '\0';
    
    //@TODO bon jusqu'ici, apres c'est a voir :

// inutile ?
//    if(strstr(msg, "\n") == NULL) {
//        fprintf(ERROROUTPUT, "sendGet error, massage is not terminated properly.\n");
//    }

    if ( send(clientSocket, msg, length,0) == -1 )
    {
        perror("sendGet error.");
        return 0;
    }
    return 1;
}


/* splitStatusLine.
*/
int splitStatusLine(char *statusLine, int* statusCode, char* statusMessage)
{
	if(!strncmp(statusLine,"STATUS_CODE_OK",2))
	{
		*statusCode = STATUS_CODE_OK;
		strncpy(statusMessage,REASON_PHRASE_OK,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_CREATED",2))
	{
		*statusCode = STATUS_CODE_CREATED;
		strncpy(statusMessage,REASON_PHRASE_CREATED,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_BAD_REQUEST",2))
	{
		*statusCode = STATUS_CODE_BAD_REQUEST;
		strncpy(statusMessage,REASON_PHRASE_BAD_REQUEST,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_NOT_CREATED",2))
	{
		*statusCode = STATUS_CODE_NOT_CREATED;
		strncpy(statusMessage,REASON_PHRASE_NOT_CREATED,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_INTERNAL_SERVER_ERROR",2))
	{
		*statusCode = STATUS_CODE_INTERNAL_SERVER_ERROR;
		strncpy(statusMessage,REASON_PHRASE_INTERNAL_SERVER_ERROR,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_CONFLICT",2))
	{
		*statusCode = STATUS_CODE_CONFLICT;
		strncpy(statusMessage,REASON_PHRASE_CONFLICT,12);
	}
	else if(!strncmp(statusLine,"STATUS_CODE_FORBIDDEN",2))
	{
		*statusCode = STATUS_CODE_FORBIDDEN;
		strncpy(statusMessage,REASON_PHRASE_FORBIDDEN,12);
	}
	else
	{
		if(statusLine[0]=='-')
			*statusCode = 0 - statusLine[1] - '0';
		else
			*statusCode = 10 * (statusLine[0] - '0') + statusLine[1] - '0';
		strncpy(statusMessage,&statusLine[3],12);
		return FALSE;
	}
	return TRUE;
}


/* splitResponseHeader.
*/
int splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType)
{
	int i = 0;
	int multiplicator = 1;
	
	for(i=0;i<15;i++)
		multiplicator *= 10;
		
	*contentLength = 0;
	
	for(i=16;i<16+15;i++)
	{
		*contentLength += multiplicator * (responseHeaderField[i] - '0');
		multiplicator /= 10;
	}
	
	strncpy(contentType,&responseHeaderField[46],16);
	
	return 0;
}


/* Ferme la connexion.
 */
void Terminaison() {
    close(clientSocket);
}
