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
int Init(char *port)
{
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
            return ERROR_UNKNOWN;
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
            break;          /* SUCCESSs */

        close(listenSocket);    /* bind error, close and try next one */
    } while ( (res = res->ai_next) != NULL);

    if (res == NULL) {
            perror("bind error");
            return ERROR_UNKNOWN;
    }

    adressLength = res->ai_addrlen;

    freeaddrinfo(ressave);
    listen(listenSocket, 4);
    printf("Init sucess\n");

    return SUCCESS;
}


/* connectWait.
 *
*/
int connectWait()
{
    struct sockaddr *clientAddr;
    char machine[NI_MAXHOST];

    clientAddr = (struct sockaddr*) malloc(adressLength);
    mainSocket = accept(listenSocket, clientAddr, &adressLength);
    if (mainSocket == -1) {
        perror("connectWait error.");
        return ERROR_UNKNOWN;
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

    return SUCCESS;
}


/* receiveBinary.
 *
*/
int receiveBinary(char *data)
{
    free(data);
    data=NULL;

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
    return SUCCESS;
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
            strcpy(statusLine, "STATUS_CODE_OK");     // <<-- `"STATUS_CODE"` convert `STATUS_CODE` into a char array, and `strcpy` copy it into the message
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

    statusLine[2] = ' '; // space between status code and reason phrase

    switch(statusCode)
    {
        case STATUS_CODE_OK:
            strcpy(&statusLine[3], REASON_PHRASE_OK); // copy the reason phrase into the message
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

    statusLine[15] = '\n'; // end of the line

    statusLine[16] = '\0'; // end of this message


    return sendString(statusLine); // send this message, it's composed of characters (valid char array)
}


/* sendHeaderField.
 *
*/
int sendHeaderField(int size, int type)
{
    int temp = SUCCESS; // state of this function
    char headerField [RESPONSE_HEADER_LENGTH + 1]; // message

    strcpy(headerField,RESPONSE_HEADER_FIELDNAME_CONTENT_LENGTH); // copy into the message the Size title

    sprintf(&headerField[16],"%*d",size,15); // write `size` into the message, but with 15 chars maximum

    headerField[31] = ';'; // delimiter

    strcpy(&headerField[32],RESPONSE_HEADER_FIELDNAME_CONTENT_TYPE); // copy into the message the Content title

    switch(type)
    {
        case CONTENT_TYPE_OBJECTBID_ID:
            strcpy(&headerField[46], "ObjectBid");
            break;
        case CONTENT_TYPE_USERACCOUNT_ID:
            strcpy(&headerField[46], "UserAccount");
            break;
        default:
            temp = ERROR_WRONG_TYPE;
            break;
    }

    headerField[62] = ';'; // delimiter
    headerField[63] = '\n'; // end of the line

    headerField[64] = '\0'; // end of the message


    if(temp == SUCCESS) // if correctly made > try to send it
        temp = sendString(headerField); // send this message, it's composed of characters (valid char array)

    return temp; // is it correctly made and send ?
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
            && (request[size-2] == ';')
            && (request[size-1] == '\n') )
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
            && (request[size-2] == ';')
            && (request[size-1] == '\n') )
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
            && (request[size-2] == ';')
            && (request[size-1] == '\n') )
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
            && (request[size-2] == ';')
            && (request[size-1] == '\n') )
            return TRUE;
    return FALSE;
}


/* splitGetRequest.
 *
*/
int splitGetRequest(char* request, int size, char* data, int* sizeData)
{
    free(data);
    data = NULL;

    *sizeData = 0;

    if (size <= 6 || size > 6 + (sizeof(ObjectBid)>sizeof(UserAccount))?sizeof(ObjectBid):sizeof(UserAccount))
    {
        // too small message
        // or too long message
        // so it's wrong
        return ERROR_READING;
    }

    *sizeData = size - 4 - 2; // size of the PDU = size of the message - size of known parts ('GET' + ' ' + ';' + '\n')
    data = strndup(&request[4], *sizeData); // PDU start here, so clone it

    return SUCCESS;
}


/* splitPutRequest.
 *
*/
int splitPutRequest(char* request, int size, char* data, int* sizeData)
{
    // work the same way

    free(data);
    data = NULL;

    *sizeData = 0;

    if (size <= 6 || size > 6 + (sizeof(ObjectBid)>sizeof(UserAccount))?sizeof(ObjectBid):sizeof(UserAccount))
    {
        return ERROR_READING;
    }

    *sizeData = size - 4 - 2;
    data = strndup(&request[4], *sizeData);

    return (*sizeData == 0) ? ERROR_EMPTY_BUFF : SUCCESS; // no data <==> size == 0, so error due to empty PDU
    //there is no way to execute a put request without data
}


/* splitConnectRequest.
 *
*/
int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword)
{
    free(login);
    free(password);
    login = NULL;
    password = NULL;

    *sizeLogin = 0;
    *sizePassword = 0;

    if (size != 64)
    {
        return ERROR_READING;
    }

    login = strndup(&request[8], USERACCOUNT_LOGIN_LENGTH);
    password = strndup(&request[8+USERACCOUNT_LOGIN_LENGTH], USERACCOUNT_PASSWORD_LENGTH);

    *sizeLogin = (strlen(login)>USERACCOUNT_LOGIN_LENGTH)?USERACCOUNT_LOGIN_LENGTH:strlen(login);
    *sizePassword = (strlen(password)>USERACCOUNT_PASSWORD_LENGTH)?USERACCOUNT_PASSWORD_LENGTH:strlen(password);

    return (*sizeLogin == 0 || *sizePassword == 0) ? ERROR_EMPTY_BUFF : SUCCESS;
}


/* splitDeleteRequest.
 *
*/
int splitDeleteRequest(char* request, int size, char* data, int* sizeData)
{
    free(data);
    data = NULL;

    *sizeData = 0;

    if (size <= 9 || size > 9 + (sizeof(ObjectBid)>sizeof(UserAccount))?sizeof(ObjectBid):sizeof(UserAccount))
    {
        return ERROR_READING;
    }

    *sizeData = size - 7 - 2;
    data = strndup(&request[7], *sizeData);

    return (*sizeData == 0) ? ERROR_EMPTY_BUFF : SUCCESS;
}
