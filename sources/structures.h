#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

#include "defines.h"


typedef struct CONTENT_TYPE_OBJECTBID_NAME
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
} CONTENT_TYPE_OBJECTBID_NAME;


typedef struct CONTENT_TYPE_USERACCOUNT_NAME
{
    char type;
    long int id;
    char name[USERACCOUNT_NAME_LENGTH];
    char lastname[USERACCOUNT_LASTNAME_LENGTH];
    char adress[USERACCOUNT_ADRESS_LENGTH];
    char mail[USERACCOUNT_MAIL_LENGTH];
} CONTENT_TYPE_USERACCOUNT_NAME;



/* clearBuffer.
 * clear the buffer
*/
void clearBuffer();


/* cleanCRString.
 * clean a string from all carriage return ('\n' & '\r)
*/
void cleanCRString(char *string);


/* charInput.
 * character input, delete '\n' and EOF symbols
 * return a character
*/
char charInput();


/* mailCheck.
 * check if 'mail' string of 'length' length is a correct mail address
 * return TRUE or FALSE
*/
int mailCheck(char *mail, int taille);


/* userInput.
 * ask user to enter informations to create an UserAccount,
 * except the user id !
 * modify the input UserAccount
*/
void userInput(UserAccount * account);


/* sellInput.
 * ask the user for information to create an ObjectBid,
 * except fields
 *      id
 *      idVendor
 *      currentBidPrice
 *      currentBidIdBuyer
 * and modify the input ObjectBid
*/
void sellInput(ObjectBid * bid);


/* accSave.
 * Save account's informations into the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int accSave (UserAccount user, FILE* f);


/* accLoad.
 * Load account's informations from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int accLoad (UserAccount *user, FILE* f);


/* allAccSave.
 * Save a table of accounts from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allAccSave (UserAccount *user, int size);


/* allAccLoad.
 * Load a table of accounts from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allAccLoad (UserAccount **user, int *size);


/* objSave.
 * Save object's informations into the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objSave (ObjectBid obj, FILE* f);


/* objLoad.
 * Load object's informations into the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objLoad (ObjectBid *obj, FILE* f);


/* allObjSave.
 * Save a table of objects from the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allObjSave (UserAccount *user, int size);


/* allObjLoad.
 * Load a table of objects from the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allObjLoad (UserAccount **user, int *size);


/* file_length.
 *
*/
size_t file_length(char *filename);


//


#endif
