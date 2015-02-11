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

#include "structures.h"
#include "client.h"
#include "interfaceClient.h"


int clientSocket;
char clientBuffer[BUFFER_LENGTH];
int bufferStart;
int bufferEnd;
int connectEnd = FALSE;


/* Init.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 */
int Init(char *machine) {
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
            break;      /* SUCCESSs */

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


/* sendGetObjectBid.
*/
int sendGetObjectBid(ObjectBid *object)
{
    int length = 6 + sizeof(ObjectBid);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_GET);
    msg[strlen(REQUEST_METHOD_GET )] = ' ';

    for ( i = 4 ; i < length ; i++ )
    {
        msg[i] = ((char*)object)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
}


/* sendGetAllObjectBid.
*/
int sendGetAllObjectBid()
{
    int length = 6 ;
    char msg[length+1];

	/* @DEBUG */printf("Jusque là tout va bien.\n");

    strcpy(msg,REQUEST_METHOD_GET);
    msg[strlen(REQUEST_METHOD_GET )] = ' ';

/* @DEBUG */printf("Jusque là tout va bien.\n");

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

/* @DEBUG */printf("Jusque là tout va bien.\n");

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    
    /* @DEBUG */printf("Ok pour le sendGetAllObjectBid\n");
    return SUCCESS;
}


/* sendPutObjectBid.
*/
int sendPutObjectBid(ObjectBid *object)
{
    int length = 6 + sizeof(ObjectBid);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_PUT);
    msg[strlen(REQUEST_METHOD_PUT )] = ' ';

    for ( i = 4 ; i < length ; i++ )
    {
        msg[i] = ((char*)object)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
}


/* sendDeleteObjectBid.
*/
int sendDeleteObjectBid(ObjectBid *object)
{
    int length = 9 + sizeof(ObjectBid);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_DELETE);
    msg[strlen(REQUEST_METHOD_DELETE )] = ' ';

    for ( i = 7 ; i < length ; i++ )
    {
        msg[i] = ((char*)object)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
}


/* sendGetUserAccount.
*/
int sendGetUserAccount(UserAccount *account)
{
    int length = 6 + sizeof(UserAccount);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_GET);
    msg[strlen(REQUEST_METHOD_GET )] = ' ';

    for ( i = 4 ; i < length ; i++ )
    {
        msg[i] = ((char*)account)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
}


/* sendPutUserAccount.
*/
int sendPutUserAccount(UserAccount *account)
{
    int length = 6 + sizeof(UserAccount);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_PUT);
    msg[strlen(REQUEST_METHOD_DELETE )] = ' ';

    for ( i = 4 ; i < length ; i++ )
    {
        msg[i] = ((char*)account)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
}


/* sendDeleteUserAccount.
*/
int sendDeleteUserAccount(UserAccount *account)
{
    int length = 9 + sizeof(UserAccount);
    int i = 0;
    char msg[length+1];

    strcpy(msg,REQUEST_METHOD_DELETE);
    msg[strlen(REQUEST_METHOD_DELETE )] = ' ';

    for ( i = 7 ; i < length ; i++ )
    {
        msg[i] = ((char*)account)[i];
    }

    msg[length-2] = ';';
    msg[length-1] = '\n';
    msg[length] = '\0';

    if ( send(clientSocket, msg, length, 0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
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

    if ( send(clientSocket, msg, length,0) == -1 )
    {
        perror("sendGet error.");
        return ERROR_SENDING;
    }
    return SUCCESS;
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

/* accountCreation.
*/
int accountCreation()
{
    int statusCode;
    char response[STATUS_LINE_LENGTH];
    char * reasonPhrase=NULL;
    UserAccount acc;

    /* Get the informations about the new account */
    userInputUserAccount(&acc);

    /* Try to send the request.
     * If the answer is not CREATED, resend it */
    int i=0;
    while (statusCode != STATUS_CODE_CREATED && i < 3)
    {
        /* Send the new account to the server */
        sendPutUserAccount(&acc);

        /* Get the answer */
        receiveBinary(response,STATUS_LINE_LENGTH);

        /* Extract the status code and the reason phrase from the answer */
        splitStatusLine(response,&statusCode,reasonPhrase);

        i++;
    }

    /* Display the result */
    displayResult(statusCode);

    return SUCCESS;
}

/* connection.
*/
int connection ()
{
    int statusCode;
    char response[STATUS_LINE_LENGTH];
    char * reasonPhrase=NULL;
    char login[USERACCOUNT_LOGIN_LENGTH];
    char password[USERACCOUNT_PASSWORD_LENGTH];

    /* Ask for a login and a password */
    connectionInput(login,password);

    /* Try to send the request.
     * If the answer is NOT_CREATED, resend it */
    int i=0;
    while (statusCode == STATUS_CODE_NOT_CREATED && i < 3)
    {
        /* Send a connection request to the server */
        sendConnect(login,password);

        /* Get the answer's status line */
        receiveBinary(response,STATUS_LINE_LENGTH);

        /* Extract the status code and the reason phrase from the answer */
        splitStatusLine(response,&statusCode,reasonPhrase);

        i++;
    }

    /* Display the result */
    displayResult(statusCode);

    if (statusCode == STATUS_CODE_OK)
        return SUCCESS;
    else
        return CONNECTION_DENIED;
}

/* listObjects
*/
int listObjects (ObjectBid ** list, size_t* listSize)
{
    int statusCode;
    int i = 0;
    char statLine[STATUS_LINE_LENGTH];
    char headers[RESPONSE_HEADER_FIELD_LENGTH];
    char contentType[RESPONSE_HEADER_FIELD_CONTENT_TYPE_LENGTH];
    char * reasonPhrase=NULL;

    /* Send the request, 3 try */
    while (statusCode != STATUS_CODE_OK && i < 3)
    {
        /* Send the request */
        sendGetAllObjectBid();

        /* Get the answer's status line */
        receiveBinary(statLine,STATUS_LINE_LENGTH);

        /* Extract the status code and the reason phrase from the answer */
        splitStatusLine(statLine,&statusCode,reasonPhrase);

        i++;
    }

    /* Display the result of the request */
    displayResult(statusCode);

    if (statusCode == STATUS_CODE_OK)
    {
		/* Get the header fields */
		receiveBinary(headers,64);
		
		/* Extract the list size from the headers */
		splitResponseHeader(headers,(int *)listSize,contentType);
		
		/* Get the list */
        receiveBinary((char*)list,*listSize);

        /* Display the list */
        displayList(*list,*listSize);

        return SUCCESS;
    }
    else
        return ERROR_RECEIVING;
}

/* searchObject
*/
int searchObject (ObjectBid * list, size_t listSize)
{
    ObjectBid * result=NULL;
    char* name=NULL;
    int i=0;
    int resultNumber=0;

    /* If there is no list, display an error */
    if (list==NULL)
    {
        displayResult(ERROR_NO_LIST);
    }

    /* Ask the user for an object name */
    searchInput(name);

	/* Search for the name of the object in the list */
	for (i=0;i<(int)(listSize/sizeof(ObjectBid));i++)
	{
		/* If the name of the current object match */
		if (strcmp(name,list[i].name) == 0)
		{
			/* Extend the result list */
			resultNumber++;
			result=realloc(result,resultNumber*sizeof(ObjectBid));
			
			/* Add the current object to the result list */
			result[resultNumber-1]=list[i];
		}
	}

    /* Display the result */
    displayList(result,resultNumber*sizeof(ObjectBid));

    return SUCCESS;
}

/* bidObject
*/
int bidObject ()
{
	return SUCCESS;
}


/* Ferme la connexion.
 */
void Terminaison() {
    close(clientSocket);
}


