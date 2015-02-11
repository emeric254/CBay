#ifndef __CLIENT_H__
#define __CLIENT_H__


/* Init.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int Init(char *server);


/* receiveBinary.
 * renvoie le nombre d'octets reus, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int receiveBinary(char *donnees, size_t tailleMax);


/* sendBinary.
 * renvoie le nombre d'octets envoys, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int sendBinary(char *donnees, size_t taille);


/* sendGetObjectBid.
 *
*/
int sendGetObjectBid(ObjectBid *object);


/* sendGetAllObjectBid.
 *
*/
int sendGetAllObjectBid();


/* sendPutObjectBid.
 *
*/
int sendPutObjectBid(ObjectBid *object);


/* sendDeleteObjectBid.
 *
*/
int sendDeleteObjectBid(ObjectBid *object);


/* sendGetUserAccount.
 *
*/
int sendGetUserAccount(UserAccount *account);


/* sendPutUserAccount.
 *
*/
int sendPutUserAccount(UserAccount *account);


/* sendDeleteUserAccount.
 *
*/
int sendDeleteUserAccount(UserAccount *account);


/* sendConnect.
 *
*/
int sendConnect(char* login, char* password);


/* splitStatusLine.
 *
*/
int splitStatusLine(char *statusLine, int* statusCode, char* statusMessage);


/* splitResponseHeader.
 *
*/
int splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType);

/* accountCreation.
 * Asks the user for some informations and create a new UserAccount then send it
 * to the server.
*/
int accountCreation ();

/* connection.
 * Asks the user for a login and a password and try to connect to the server.
 * Return the result (SUCCESS or CONNECTION_DENIED).
*/
int connection();

/* listObjects.
 * Take the list of all the available objects from the server and display it.
 * Return the list and its size.
*/
int listObjects (ObjectBid ** list, size_t* listSize);

/* searchObject.
 * Search for an object into the list of the available ones.
 * Return the object found or nothing if the object doesn't appear in the list.
*/
int searchObject (ObjectBid * list, size_t listSize);

/* bidObject.
 * Asks the user for a bid and send it to the server. Display the result.
 * Return the result.
*/
int bidObject ();

/* Ferme la connexion.
 *
 */
void Terminaison();


#endif
