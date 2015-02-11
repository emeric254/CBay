#ifndef __CLIENT_H__
#define __CLIENT_H__


/** \fn int Init(char *server)
 * \brief Connection to the server
 * \param server is the server's adress
 * \return SUCCESS or ERROR_UNKNOWN
 *
 */
int Init(char *server);


/** \fn
 * \brief
 * \param
 * \return
 *
 */

/** \fn int receiveBinary(char *donnees, size_t tailleMax)
 * \brief receive binary datas from the server and store them in a character array
 * \param donnees is an array in which we store the incoming data and tailleMax
 * is the maximum character the function will stock in donnees
 * \return the number of received bytes, 0 for a closed connection and
 * a negative number in case of an error
 *
 */
int receiveBinary(char *donnees, size_t tailleMax);


/** \fn int sendBinary(char *donnees, size_t taille)
 * \brief send to the server datas from a character array
 * \param donnees is an array containing the data we will send and tailleMax is
 * the maximum character the function will stock in donnees
 * \return the number of sent bytes, 0 for a closed connection and
 * a negative number in case of an error
 *
 */
int sendBinary(char *donnees, size_t taille);


/** \fn int sendGetObjectBid(ObjectBid *object)
 * \brief send a request to the server to get an object
 * \param an object
 * \return status code of this operation
 *
 */
int sendGetObjectBid(ObjectBid *object);


/** \fn int sendGetAllObjectBid()
 * \brief send a request to the server to get all the objects
 * \param an object
 * \return status code of this operation
 *
 */
int sendGetAllObjectBid();


/** \fn int sendPutObjectBid(ObjectBid *object)
 * \brief send a request to the server to store an object in it
 * \param an object
 * \return status code of this operation
 *
 */
int sendPutObjectBid(ObjectBid *object);


/** \fn int sendDeleteObjectBid(ObjectBid *object)
 * \brief send a request to the server to delete an object
 * \param an object
 * \return status code of this operation
 *
 */
int sendDeleteObjectBid(ObjectBid *object);


/** \fn int sendGetUserAccount(UserAccount *account)
 * \brief send a request to the server to get an user account
 * \param an user account
 * \return status code of this operation
 *
 */
int sendGetUserAccount(UserAccount *account);


/** \fn int sendPutUserAccount(UserAccount *account)
 * \brief send a request to the server to store an user account in it
 * \param an user account
 * \return status code of this operation
 *
 */
int sendPutUserAccount(UserAccount *account);


/** \fn int sendDeleteUserAccount(UserAccount *account)
 * \brief send a request to the server to delete an user account
 * \param an user account
 * \return status code of this operation
 *
 */
int sendDeleteUserAccount(UserAccount *account);


/** \fn int sendConnect(char* login, char* password)
 * \brief send a request to the server to connect an user to the CBay service
 * \param a character array for the login and one for the password
 * \return status code of this operation
 *
 */
int sendConnect(char* login, char* password);


/** \fn splitStatusLine(char *statusLine, int* statusCode, char* statusMessage)
 * \brief take a status line and cut it in a status code and a reason phrase
 * \param the status line to cut, the status code and the statusMessage to extract
 * \return status code of this operation
 *
 */
int splitStatusLine(char *statusLine, int* statusCode, char* statusMessage);


/** \fn splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType)
 * \brief take the response header fields and extract the value of fields
 * content-length and content-type
 * \param the responseHeaderField to cut and the contentLength and contentType to
 * extract
 * \return status code of this operation
 *
 */
int splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType);


/** \fn int accountCreation()
 * \brief Asks the user for some informations and create a new UserAccount then
 * send it to the server
 * \param
 * \return status code of this operation
 *
 */
int accountCreation ();


/** \fn int connection()
 * \brief Asks the user for a login and a password and try to connect to the server 
 * \param
 * \return the result (SUCCESS or CONNECTION_DENIED)
 *
 */
int connection();


/** \fn int listObjects(ObjectBid ** list, size_t* listSize)
 * \brief Take the list of all the available objects from the server and display it
 * \param list is the list of all the objects and listSize its size in bytes
 * \return status code of this operation
 *
 */
int listObjects (ObjectBid ** list, size_t* listSize);


/** \fn int searchObject(ObjectBid * list, size_t listSize)
 * \brief Search for an object into the list of the available ones.
 * \param list is the list of all the objects and listSize its size in bytes
 * \return status code of this operation
 *
 */
int searchObject (ObjectBid * list, size_t listSize);


/** \fn int bidObject()
 * \brief Asks the user for a bid and send it to the server. Display the result.
 * \param
 * \return status code of this operation
 *
 */
int bidObject ();


/** \fn void Terminaison
 * \brief End the connection
 * \param
 * \return nothing
 *
 */
void Terminaison();


#endif
