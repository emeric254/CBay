#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "defines.h"


typedef struct ObjectBid
{
    long int id;
    char name[96];
    float basePrice;
    char description[320];
    long int idVendor;
    long int startTime;
    long int endTime;
    char adress[96];
    float  currentBidPrice;
    long int currentBidIdBuyer;
} ObjectBid;


typedef struct UserAccount
{
    char type;
    long int id;
    char name[75];
    char lastname[64];
    char adress[96];
    char mail[80];
} UserAccount;



/* videBuffer.
 * vide le buffer
*/
void videBuffer();


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
 * modifi le ObjectBid saisi
*/
void saisieVente(ObjectBid * bid);


//


#endif
