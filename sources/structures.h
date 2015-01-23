#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "defines.h"


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
 * verifie si la chaine de taille n est une adresse mail correctement constituee
 * retourne TRUE ou FALSE
*/
int verifMail(char *mail, int taille);


typedef struct
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


typedef struct
{
    char type;
    long int id;
    char name[75];
    char lastname[64];
    char adress[96];
    char mail[80];
} UserAccount;


//


#endif
