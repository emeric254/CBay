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



typedef struct
{
}ObjectBid;


typedef struct
{
	char type;
	long int id;
	char [75]name;
	char [64]lastname;
	char [96]adress;
	char [80]mail;	
} UserAccount;


/*

   7.1.1 Object bid
   |----------|----------|------------|-------------|-----------|-»
   |    ID    |   Name   | Base Price | Description | Vendor ID |-»
   |----------|----------|------------|-------------|-----------|-»
   | LONG INT | CHAR[96] |    FLOAT   |  CHAR[320]  |  LONG INT |-»
   |----------|----------|------------|-------------|-----------|-»

   «-|------------|----------|----------|-------------------|-»
   «-| Start Time | End Time |  Adress  | Current Bid Price |-»
   «-|------------|----------|----------|-------------------|-»
   «-|  LONG INT  | LONG INT | CHAR[96] |       FLOAT       |-»
   «-|------------|----------|----------|-------------------|-»

   «-|----------------------|
   «-| Current Bid Buyer ID |
   «-|----------------------|
   «-|       LONG INT       |
   «-|----------------------|

*/

//



/* ... */


#endif
