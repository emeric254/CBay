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


/* connectWait.
 *
*/
int connectWait() {
    struct sockaddr *clientAddr;
    char machine[NI_MAXHOST];

    clientAddr = (struct sockaddr*) malloc(adressLength);
    mainSocket = accept(listenSocket, clientAddr, &adressLength);
    if (mainSocket == -1) {
        perror("connectWait error.");
        return 0;
    }
    if(getnameinfo(clientAddr, adressLength, machine, NI_MAXHOST, NULL, 0, 0) == 0) {
        printf("new client conected: %s\n", machine);
    } else {
        printf("anonymous client connected.\n");
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


/* receiveBinary.
 *
*/
int receiveBinary(char *data) {
    char localBuffer[BUFFER_LENGTH];
    int index = 0;
    int received = 0;
    int end = FALSE;
    int find = FALSE;

    if (connectEnd)
        end = TRUE;

    while (end == FALSE)
    {
        // copy all the received data in localBuffer and test if the end of data char is received
        while ((bufferEnd > bufferStart) && (!find))
        {
            if (clientBuffer[bufferStart] == '\n')
                find = TRUE; // end of data char received
            else
                localBuffer[index++] = clientBuffer[bufferStart++]; // copy data to localBuffer
        }

        /* end of data char find ? */
        if (find)
        {
            localBuffer[index++] = '\n';
            localBuffer[index] = '\0';
            bufferStart++;
            end = TRUE;

#ifdef WIN32
            data = _strdup(localBuffer);
#else
            data = strdup(localBuffer);
#endif
            return index*sizeof(char); // == data size
        }
        else // all data no yet 'received'
        {
            bufferStart = 0;
            received = recv(mainSocket, clientBuffer, BUFFER_LENGTH, 0);

            if (received < 0)
            {
                perror("receiveBinary error.");
                end = TRUE;
            }
            else if (!received) // that's all
            {
                connectEnd = TRUE;

                if (index > 0) // is there data in localBuffer ?
                {
                    localBuffer[index++] = '\n';
                    localBuffer[index] = '\0';
#ifdef WIN32
                    data = _strdup(localBuffer);
#else
                    data = strdup(localBuffer);
#endif
                return index * sizeof(char); // == data size
                }
                else
                {
                    // nothing received
                    return ERROR_EMPTY_BUFF;
                }
            }
            else
            {
                // 'received' octets more received
                bufferEnd = received;
            }
        }
    }
    return ERROR_RECEIVING;
}


/* sendBinary.
 *
*/
int sendBinary(char *data, size_t size)
{
    int temp = 0;
    temp = send(mainSocket, data, size, 0);
    if(temp == -1) {
        perror("sendBinary error.");
        return ERROR_SENDING;
    } else {
        return temp;
    }
}


/* sendString.
 *
 */
int sendString(char *string)
{
    int length = strlen(string);
    if (send(mainSocket, string, length,0) == -1) {
        perror("sendString error.");
        return ERROR_SENDING;
    }
    return SUCESS;
}


/* endClient.
 *
*/
void endClient()
{
    close(mainSocket);
}


/* endServer.
 *
*/
void endServer()
{
    close(listenSocket);
}


/* sendStatusLine.
 *
*/
int sendStatusLine(int statusCode)
{
    char statusLine[STATUS_LINE_LENGTH + 1];

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

    return sendString(statusLine);;
}


/* sendHeaderField.
 *
*/
int sendHeaderField(int size, int type)
{
    int temp = SUCESS;
    char headerField [RESPONSE_HEADER_LENGTH + 1];

    strcpy(headerField,RESPONSE_HEADER_FIELDNAME_CONTENT_LENGTH);

    sprintf(&headerField[16],"%*d",size,15);

    headerField[31] = ';';

    strcpy(&headerField[32],RESPONSE_HEADER_FIELDNAME_CONTENT_TYPE);

    switch(type)
    {
        case CONTENT_TYPE_OBJECTBID_ID:
            strcpy(&headerField[46],"ObjectBid");
            break;
        case CONTENT_TYPE_USERACCOUNT_ID:
            strcpy(&headerField[46],"UserAccount");
            break;
        default:
            temp = ERROR_WRONG_TYPE;
            break;
    }

    headerField[62] = ';';
    headerField[63] = '\n';
    headerField[64] = '\0';

    if(temp == SUCESS)
        temp = sendString(headerField);

    return temp;
}


/* isGetRequest.
 *
*/
int isGetRequest(char* request, int size)
{
    // REQUEST_METHOD_GET
    if (size >= 6)
        if ( (!strncmp(request,REQUEST_METHOD_GET,strlen(REQUEST_METHOD_GET)))
            && (request[strlen(REQUEST_METHOD_GET)] == ' ')
            && (request[size-1] == '\n')
            && (request[size-2] == ';') )
            return TRUE;
    return FALSE;
}


/* isPutRequest.
 *
*/
int isPutRequest(char* request, int size)
{
    // REQUEST_METHOD_PUT
    if (size >= 6)
        if ( (!strncmp(request,REQUEST_METHOD_PUT,strlen(REQUEST_METHOD_PUT)))
            && (request[strlen(REQUEST_METHOD_PUT)] == ' ')
            && (request[size-1] == '\n')
            && (request[size-2] == ';') )
            return TRUE;
    return FALSE;
}


/* isConnectRequest.
 *
*/
int isConnectRequest(char* request, int size)
{
    // REQUEST_METHOD_CONNECT
    if (size == 64)
        if ( (!strncmp(request,REQUEST_METHOD_CONNECT,strlen(REQUEST_METHOD_CONNECT)))
            && (request[strlen(REQUEST_METHOD_CONNECT)] == ' ')
            && (request[35] == ';')
            && (request[size-1] == '\n')
            && (request[size-2] == ';') )
            return TRUE;
    return FALSE;
}


/* isDeleteRequest.
 *
*/
int isDeleteRequest(char* request, int size)
{
    // REQUEST_METHOD_DELETE
    if (size >= 9)
        if ( (!strncmp(request,REQUEST_METHOD_DELETE,strlen(REQUEST_METHOD_DELETE)))
            && (request[strlen(REQUEST_METHOD_DELETE)] == ' ')
            && (request[size-1] == '\n')
            && (request[size-2] == ';') )
            return TRUE;
    return FALSE;
}


/* splitGetRequest.
 *
*/
int splitGetRequest(char* request, int size, char* data, int* sizeData)
{
    data = NULL;
    *sizeData = 0;
    if (size > 6)
    {
        data = &request[4];
        *sizeData = size - 4 - 2;
    }
    return SUCESS;
}


/* splitPutRequest.
 *
*/
int splitPutRequest(char* request, int size, char* data, int* sizeData)
{
    data = NULL;
    *sizeData = 0;
    if (size > 9)
    {
        data = &request[7];
        *sizeData = size - 7 - 2;
    }
    return (*sizeData == 0) ? ERROR_EMPTY_BUFF : SUCESS;
}


/* splitConnectRequest.
 *
*/
int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword)
{
    login = NULL;
    password = NULL;
    *sizeLogin = 0;
    *sizePassword = 0;
    if (size == 64)
    {
        login = &request[8];
        password = &request[8+USERACCOUNT_LOGIN_LENGTH];
        sizeLogin = (strlen(login)>USERACCOUNT_LOGIN_LENGTH)?USERACCOUNT_LOGIN_LENGTH:strlen(login);
        sizePassword = (strlen(password)>USERACCOUNT_PASSWORD_LENGTH)?USERACCOUNT_PASSWORD_LENGTH:strlen(password);
    }
    return (*sizeLogin == 0 || *sizePassword == 0) ? ERROR_EMPTY_BUFF : SUCESS;
}


/* splitDeleteRequest.
 *
*/
int splitDeleteRequest(char* request, int size, char* data, int* sizeData)
{
    data = NULL;
    *sizeData = 0;
    if (size > 6)
    {
        data = &request[4];
        *sizeData = size - 4 - 2;
    }
    return (*sizeData == 0) ? ERROR_EMPTY_BUFF : SUCESS;
}
