#ifndef __CLIENT_H__
#define __CLIENT_H__


/* Initialisation.
 * Connexion au serveur sur la machine donnee.
 * Utilisez localhost pour un fonctionnement local.
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int Init(char *server);


/* Recoit des donnees envoyees par le serveur.
 * renvoie le nombre d'octets reus, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int receiveBinary(char *donnees, size_t tailleMax);


/* Envoie des donnes au serveur en prcisant leur taille.
 * renvoie le nombre d'octets envoys, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int sendBinary(char *donnees, size_t taille);


/*
*/
int sendGet();


/*
*/
int sendPut();


/*
*/
int sendDelete();


/*
*/
int sendConnect(char* login, char* password);


/*
*/
int splitStatusLine(char *statusLine, int* statusCode, char* statusMessage);


/*
*/
int splitResponseHeader(char *responseHeaderField, int* contentLength, char* contentType);


/* Ferme la connexion.
 */
void Terminaison();


#endif
