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
int Init(char *port);


/** \fn int connectWait()
 * \brief wait for a client to connect, and then open the connection with him
 * \return status code of this operation.
 *
 */
int connectWait();


/** receiveBinary.
 * \brief
 * \param
 * \return
 *
 */
int receiveBinary(char *data);


/** sendBinary.
 * \brief
 * \param
 * \return
 *
 */
int sendBinary(char *data, size_t size);


/** sendString.
 * \brief
 * \param
 * \return
 *
 */
int sendString(char *data);


/** endClient.
 * \brief
 *
*/
void endClient();


/** endServer.
 * \brief
 *
*/
void endServer();


/** sendStatusLine.
 * \brief
 * \param
 * \return
 *
*/
int sendStatusLine(int statusCode);


/** sendHeaderField
 * \brief
 * \param
 * \param
 * \return
 *
*/
int sendHeaderField(int size, int type);


/** isGetRequest.
 * \brief
 * \param
 * \param
 * \return
 *
*/
int isGetRequest(char* request, int size);


/** isPutRequest.
 * \brief
 * \param
 * \param
 * \return
 *
*/
int isPutRequest(char* request, int size);


/** isConnectRequest.
 * \brief
 * \param
 * \param
 * \return
 *
*/
int isConnectRequest(char* request, int size);


/** isDeleteRequest.
 * \brief
 * \param
 * \param
 * \return
 *
*/
int isDeleteRequest(char* request, int size);


/** splitGetRequest.
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 *
*/
int splitGetRequest(char* request, int size, char* data, int* sizeData);


/** splitPutRequest.
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 *
*/
int splitPutRequest(char* request, int size, char* data, int* sizeData);


/** splitConnectRequest.
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \param
 * \param
 * \return
 *
*/
int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword);


/** splitDeleteRequest.
 * \brief
 * \param
 * \param
 * \param
 * \param
 * \return
 *
*/
int splitDeleteRequest(char* request, int size, char* data, int* sizeData);


#endif
