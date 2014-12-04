#ifndef __SERVEUR_H__
#define __SERVEUR_H__

/* Initialisation.
 * Creation du serveur.
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int Initialisation();

/* Initialisation.
 * Creation du serveur en prcisant le service ou numro de port.
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int InitialisationAvecService(char *service);


/* Attends qu'un client se connecte.
 * renvoie 1 si a c'est bien pass 0 sinon
 */
int AttenteClient();

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

/* Recoit des donnees envoyees par le client.
 * renvoie le nombre d'octets reus, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int ReceptionBinaire(char *donnees, size_t tailleMax);

/* Envoie des donnes au client en prcisant leur taille.
 * renvoie le nombre d'octets envoys, 0 si la connexion est ferme,
 * un nombre ngatif en cas d'erreur
 */
int EmissionBinaire(char *donnees, size_t taille);


/* Ferme la connexion avec le client.
 */
void TerminaisonClient();

/* Arrete le serveur.
 */
void Terminaison();

// ----------------------------------------------------

/* ex 8.a
*/
int extraitFichier(char *requete, char **nomFichier, size_t *maxNomFichier) ;

/* ex 8.b
*/
size_t longueur_fichier(char *nomFichier);

/* ex 8.c
*/
int envoyerContenuFichierTexte(char *nomFichier);

/* ex 8.d
*/
int envoyerReponse200HTML(char *nomFichier);

/* ex 8.e
*/
int envoyerReponse404();

/* ex 8.f
*/
int envoyerReponse500();

/* ex 11.a
*/
int envoyerContenuFichierBinaire(char *nomFichier);

/* ex 11.b
*/
int envoyerReponse200JPG(char *nomFichier);

/* ex 13.a
*/
int envoyerReponse200ICO(char *nomFichier);

/* autres
*/
int testExtension(char *nomFichier, char *extension);

int envoyerReponse400();

int envoyerReponse403();

#endif