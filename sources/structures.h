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
    char [96]name;
    float basePrice;
    char [320]description;
    long int idVendor;
    long int startTime;
    long int endTime;
    char[96] adress;
    float  currentBidPrice;
    long int currentBidIdBuyer;
} ObjectBid;


typedef struct
{
    char type;
    long int id;
    char [75]name;
    char [64]lastname;
    char [96]adress;
    char [80]mail;
} UserAccount;


//


#endif
