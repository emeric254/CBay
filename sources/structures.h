#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "defines.h"


typedef struct ObjectBid
{
    long int id;
    char name[OBJECTBID_NAME_LENGTH];
    float basePrice;
    char description[OBJECTBID_DESCRIPTION_LENGTH];
    long int idVendor;
    long int startTime;
    long int endTime;
    char adress[OBJECTBID_ADRESS_LENGTH];
    float  currentBidPrice;
    long int currentBidIdBuyer;
} ObjectBid;


typedef struct UserAccount
{
    char type;
    long int id;
    char name[USERACCOUNT_NAME_LENGTH];
    char lastname[USERACCOUNT_LASTNAME_LENGTH];
    char adress[USERACCOUNT_ADRESS_LENGTH];
    char mail[USERACCOUNT_MAIL_LENGTH];
} UserAccount;



/* videBuffer.
 * vide le buffer
*/
void videBuffer();


/* cleanCRString.
 * clean a string from all carriage return ('\n' & '\r)
*/
void basePrice(char *string);

/* saisieChar.
 * saisie d'un caractere, elimine les '\n' et EOF
 * retourne un caractere
*/
char saisieChar();


/* verifMail.
 * verifie si la chaine 'mail' de taille 'taille' est une adresse mail correctement constituee
 * retourne TRUE ou FALSE
*/
int verifMail(char *mail, int taille);


/* saisieUtilisateur.
 * fais saisir a l'utilisateur un UserAccount,
 * sauf l'id !
 * modifi le UserAccount saisi
*/
void saisieUtilisateur(UserAccount * account);


/* saisieVente.
 * fais saisir a l'utilisateur un ObjectBid,
 * sauf les champs
 *      id
 *      idVendor
 *      currentBidPrice
 *      currentBidIdBuyer
 * modifie le ObjectBid saisi
*/
void saisieVente(ObjectBid * bid);

/* accSave
 * Save account's informations into the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int accSave (UserAccount user);

/* accLoad
 * Load account's informations from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int accLoad (UserAccount *user);

/* objSave
 * Save object's informations into the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objSave (ObjectBid obj);


/* objLoad
 * Load object's informations into the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objLoad (ObjectBid *obj);

//


#endif
