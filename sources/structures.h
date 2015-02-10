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


typedef struct ConfidentialIDS
{
    long int id;
    char login[USERACCOUNT_LOGIN_LENGTH];
    char password[USERACCOUNT_PASSWORD_LENGTH];
} ConfidentialIDS;


/* cleanBuffer.
 * clear the buffer
*/
void cleanBuffer();


/* cleanCRString.
 * clean a string from all carriage return ('\n' & '\r)
*/
void cleanCRString(char *string);


/* getAChar.
 * character input, delete '\n' and EOF symbols
 * return a character
*/
char getAChar();


/* validMail.
 * check if 'mail' string of 'length' length is a correct mail address
 * return TRUE or FALSE
*/
int validMail(char *mail, int taille);


/* userInputUserAccount.
 * ask user to enter informations to create an UserAccount,
 * except the user id !
 * modify the input UserAccount
*/
void userInputUserAccount(UserAccount * account);


/* userInputObjectBid.
 * ask the user for information to create an ObjectBid,
 * except fields
 * id
 * idVendor
 * currentBidPrice
 * currentBidIdBuyer
 * and modify the input ObjectBid
*/
void userInputObjectBid(ObjectBid * bid);


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


/* userInTable.
 * test if an user's account is in the table or not, and return its id or not.
 * return TRUE if it's contain (ids matching), return FALSE otherwise.
 */
int userInTable (UserAccount *user, UserAccount *table, int size, long int *id);


/* allAccSave.
 * Save a table of accounts from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allAccSave (UserAccount *table, int size);


/* allAccLoad.
 * Load a table of accounts from the ACC_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allAccLoad (UserAccount **table, int *size);


/* objSave.
 * Save object's informations into the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objSave (ObjectBid obj, FILE* f);


/* objLoad.
 * Load object's informations from the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int objLoad (ObjectBid *obj, FILE* f);


/* objInTable.
 * test if an object is in the table or not, and return its id or not.
 * return TRUE if it's contain (ids matching), return FALSE otherwise.
 */
int objInTable (ObjectBid *obj, ObjectBid *table, int size, long int *id);


/* allObjSave.
 * Save a table of objects from the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allObjSave (ObjectBid *table, int size);


/* allObjLoad.
 * Load a table of objects from the OBJ_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allObjLoad (ObjectBid **table, int *size);


/* idsLoad.
 * Load ids's informations from the IDS_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int idsLoad (ConfidentialIDS *ids, FILE *f);


/* allIDSLoad.
 * Load a table of IDS from the IDS_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allIDSLoad (ConfidentialIDS **table, int *size);


/* allIDSLoad.
 * Save a table of IDS to the IDS_FILE.
 * Integer return codes correspond to the operation's outcome.
 */
int allIDSSave (ConfidentialIDS **table, int *size);


/* idsInTable.
 * test if ids are in the IDS table, and return its id or not.
 * return TRUE if it's contain (ids matching), return FALSE otherwise.
 */
int idsInTable (char login[USERACCOUNT_LOGIN_LENGTH], char password[USERACCOUNT_PASSWORD_LENGTH], ConfidentialIDS *table, int size, long int *id);


/* file_length.
 *
*/
size_t file_length(char *filename);


//


#endif
