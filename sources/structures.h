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

   7.1.2 User account
   |------|----------|----------|-----------|----------|----------|
   | Type |    ID    |   Name   |  Lastname |  Adress  |   Mail   |
   |------|----------|----------|-----------|----------|----------|
   | CHAR | LONG INT | CHAR[75] |  CHAR[64] | CHAR[96] | CHAR[80] |
   |------|----------|----------|-----------|----------|----------|

*/

//



/* ... */


#endif
