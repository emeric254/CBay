#ifndef __SERVEUR_H__
#define __SERVEUR_H__


/* Init.
 *
 */
int Init(char *port);


/* connectWait.
 *
 */
int connectWait();


/* Recoit un message envoye par le client.
 * retourne le message ou NULL en cas d'erreur.
 * Note : il faut liberer la memoire apres traitement.
 */
char *Reception();


/* Envoie un message au client.
 * Attention, le message doit etre termine par \n
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int Emission(char *message);


/* receiveBinary.
 *
 */
int receiveBinary(char *data);


/* sendBinary.
 *
 */
int sendBinary(char *data, size_t size);


/* endClient.
 *
*/
void endClient();


/* endServer.
 *
*/
void endServer();


/* sendStatusLine.
 *
*/
int sendStatusLine(int statusCode);


/* sendHeaderField
 *
*/
int sendHeaderField(int size, int type);


/* isGetRequest.
 *
*/
int isGetRequest(char* request, int size);


/* isPutRequest.
 *
*/
int isPutRequest(char* request, int size);


/* isConnectRequest.
 *
*/
int isConnectRequest(char* request, int size);


/* isDeleteRequest.
 *
*/
int isDeleteRequest(char* request, int size);


/* splitGetRequest.
 *
*/
int splitGetRequest(char* request, int size, char* data, int* sizeData);


/* splitPutRequest.
 *
*/
int splitPutRequest(char* request, int size, char* data, int* sizeData);


/* splitConnectRequest.
 *
*/
int splitConnectRequest(char* request, int size, char* login, char* password, int* sizeLogin, int* sizePassword);


/* splitDeleteRequest.
 *
*/
int splitDeleteRequest(char* request, int size, char* data, int* sizeData);

/*

int envoyerContenuFichierTexte(char *nomFichier);

int envoyerContenuFichierBinaire(char *nomFichier);

int testExtension(char *nomFichier, char *extension);

*/


#endif
