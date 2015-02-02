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


/* Ferme la connexion avec le client.
 */
void TerminaisonClient();


/* Arrete le serveur.
 */
void Terminaison();


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
int isGetRequest(char* data, size_t size);


/* isPutRequest.
 *
*/
int isPutRequest(char* data, size_t size);


/* isConnectRequest.
 *
*/
int isConnectRequest(char* data, size_t size);


/* isDeleteRequest.
 *
*/
int isDeleteRequest(char* data, size_t size);


/*

int envoyerContenuFichierTexte(char *nomFichier);

int envoyerContenuFichierBinaire(char *nomFichier);

int testExtension(char *nomFichier, char *extension);

*/


#endif
