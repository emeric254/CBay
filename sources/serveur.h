#ifndef __SERVEUR_H__
#define __SERVEUR_H__

/** \file serveur.h
 * \brief .........
 * This file provide some usual function for a server like \Init , \connectWait , \endClient , \endServer , \sendString or \sendBinary and \receiveBinary
 * It also contains some other derivated functions to test and play with received requests
 * plus response making functions like \sendStatusLine and \sendHeaderField .
*/


/** \fn int Init(char *port)
 * \brief initialise the server
 * \param port is the port which will be used by the server
 * \return status code of this operation.
 *
 */
int Init(char * port);


/** \fn int connectWait()
 * \brief wait for a client to connect, and then open the connection with him
 * \return status code of this operation.
 *
 */
int connectWait();


/** \fn int receiveBinary(char *data)
 * \brief receive data from the client
 * \param data is the received from the client
 * \return status code for this operation.
 *
 */
int receiveBinary(char * data);


/** \fn int sendBinary(char * data, size_t size)
 * \brief send binary data to the client
 * \param data binary data to send to the client
 * \param size data's size
 * \return status code for this operation.
 *
 */
int sendBinary(char * data, size_t size);


/** \fn int sendString(char * data)
 * \brief send a string to the client
 * \param data string to send to the client
 * \return status code for this operation.
 *
 */
int sendString(char * data);


/** \fn void endClient()
 * \brief close properly the connection with the client
 *
*/
void endClient();


/** \fn void endServer()
 * \brief close properly the server process
 *
*/
void endServer();


/** \fn int sendStatusLine(int statusCode)
 * \brief send a status line as described in the RFC
 * \param statusCode the status code to send to the client the rigth status line
 * \return status code for this operation.
 *
*/
int sendStatusLine(int statusCode);


/** \fn int sendHeaderField(int size, int type)
 * \brief send header fileds as described in the RFC
 * \param size size of the data which will be transfered
 * \param type type of the data which will be transfered
 * \return status code for this operation.
 *
*/
int sendHeaderField(int size, int type);


/** \fn int isGetRequest(char* request, int size)
 * \brief
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int isGetRequest(char* request, int size);


/** \fn int isPutRequest(char* request, int size)
 * \brief
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int isPutRequest(char* request, int size);


/** \fn int isConnectRequest(char* request, int size)
 * \brief
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int isConnectRequest(char* request, int size);


/** \fn int isDeleteRequest(char* request, int size)
 * \brief
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int isDeleteRequest(char* request, int size);


/** \fn int splitGetRequest(char* request, int size, char* data, int* sizeData)
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int splitGetRequest(char* request, int size, char* data, int* sizeData);


/** \fn int splitPutRequest(char* request, int size, char* data, int* sizeData)
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int splitPutRequest(char* request, int size, char* data, int* sizeData);


/** \fn int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword)
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword);


/** \fn int splitDeleteRequest(char* request, int size, char* data, int* sizeData)
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return status code for this operation.
 *
*/
int splitDeleteRequest(char* request, int size, char* data, int* sizeData);


#endif
