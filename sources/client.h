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


/* sendGet.
*/
int sendGet();


/* sendPut.
*/
int sendPut();


/* sendDelete.
*/
int sendDelete();


/* sendConnect.
*/
int sendConnect(char* login, char* password);


/* splitStatusLine.
*/
int splitStatusLine(char *statusLine, int* statusCode, char* statusMessage);


/* splitResponseHeader.
*/
int splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType);


/* Ferme la connexion.
 */
void Terminaison();


#endif
