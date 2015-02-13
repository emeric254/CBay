#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

/** \file structures.h
 * \brief this file provides functions for data manipulation
 * This file provides data structures and usual associated functions.
 * There is also utilities like clenBuffer.
*/


#include "defines.h"
#include <time.h>


typedef struct ConfidentialIDS
{
    long int id;
    char login[USERACCOUNT_LOGIN_LENGTH];
    char password[USERACCOUNT_PASSWORD_LENGTH];
} ConfidentialIDS;

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
    ConfidentialIDS IDS;
    char name[USERACCOUNT_NAME_LENGTH];
    char lastname[USERACCOUNT_LASTNAME_LENGTH];
    char adress[USERACCOUNT_ADRESS_LENGTH];
    char mail[USERACCOUNT_MAIL_LENGTH];
} UserAccount;




/** \fn void cleanBuffer()
 * \brief clean the buffer
 *
*/
void cleanBuffer();


/** \fn void cleanCRString(char * string)
 * \brief remove Carriage Return from a string
 * \param string string to clean
 *
*/
void cleanCRString(char * string);


/** \fn char getAChar()
 * \brief wait for a char input from the user
 * \return char input by the user
 *
*/
char getAChar();


/** \fn int mailCheck(char *mail, int taille)
 * \brief check if an input string is composed as a valid mail adress
 * \param mail the input string to test
 * \param length input string length
 * \return status code for this operation.
 *
*/
int mailCheck(char * mail, int length);


/** \fn void userInputUserAccount(UserAccount * account)
 * \brief ask the user to input fields of a new UserAccount var except ids.
 * \param account the output UserAccount
 * \return status code for this operation.
 *
*/
void userInputUserAccount(UserAccount * account);


/** \fn void userInputObjectBid(ObjectBid * bid)
 * \brief ask the user to input fields of a new ObjectBid except ids' and currentBid vars.
 * \param bid the output ObjectBid
 * \return status code for this operation.
 *
*/
void userInputObjectBid(ObjectBid * bid);


/** \fn int accSave (UserAccount user, FILE* f)
 * \brief save account's informations into the ACC_FILE
 * \param user user var to save
 * \param f file descriptor to the output file (ACC_FILE)
 * \return status code for this operation.
 *
*/
int accSave (UserAccount user, FILE * f);


/** \fn int accLoad (UserAccount *user, FILE* f)
 * \brief load account's informations from the ACC_FILE
 * \param user output user var
 * \param f file descriptor to the input file (ACC_FILE)
 * \return status code for this operation.
 *
*/
int accLoad (UserAccount * user, FILE * f);


/** \fn int userInTable (UserAccount *user, UserAccount *table, int size, long int *id)
 * \brief test if an user's account is in the table or not, and output its id or not
 * \param user input pointer to an UserAccount var
 * \param table input table of UserAccount
 * \param size size of this table
 * \param ptrUser pointer to the matching UserAccount
 * \return status code for this operation.
 * matching tests are made with ids.
*/
int userInTable (UserAccount * user, UserAccount * table, int size, UserAccount * ptrUser);


/** \fn int allAccSave (UserAccount *table, int size)
 * \brief save a table of UserAccount from the ACC_FILE
 * \param table input table to save
 * \param size size of this table
 * \return status code for this operation.
 *
*/
int allAccSave (UserAccount * table, int size);


/** \fn int allAccLoad (UserAccount **table, int *size)
 * \brief load a table of UserAccount from the ACC_FILE
 * \param table output table which will be load
 * \param size size of this table
 * \return status code for this operation.
 *
*/
int allAccLoad (UserAccount ** table, int * size);


/** \fn int objSave (ObjectBid obj, FILE* f)
 * \brief save object's informations into the OBJ_FILE
 * \param obj an ObjectBid to save
 * \param f file descriptor to the output file (OBJ_FILE)
 * \return status code for this operation.
 *
*/
int objSave (ObjectBid obj, FILE * f);


/** \fn int objLoad (ObjectBid *obj, FILE* f)
 * \brief load object's informations from the OBJ_FILE
 * \param obj the ObjectBid loaded
 * \param f file descriptor to the input file (OBJ_FILE)
 * \return status code for this operation.
 *
*/
int objLoad (ObjectBid * obj, FILE * f);


/** \fn int objInTable (ObjectBid *obj, ObjectBid *table, int size, long int *id)
 * \brief test if a given ObjectBid is in an ObjectBid table
 * \param obj input ObjectBid var pointer to test
 * \param table input ObjectBid table to search in
 * \param size size of this table
 * \param ptrObject pointer to the matching ObjectBid
 * \return status code for this operation.
 *
*/
int objInTable (ObjectBid * obj, ObjectBid * table, int size, ObjectBid * ptrObject);


/** \fn int allObjSave (ObjectBid *table, int size)
 * \brief save a table of objects to the OBJ_FILE
 * \param table input ObjectBid table to save
 * \param size size of this table
 * \return status code for this operation.
 *
*/
int allObjSave (ObjectBid * table, int size);


/** \fn int allObjLoad (ObjectBid **table, int *size)
 * \brief load a table of objects from the OBJ_FILE
 * \param table output ObjectBid table to load
 * \param size output size of this table
 * \return status code for this operation.
 *
*/
int allObjLoad (ObjectBid ** table, int * size);


/** \fn int idsLoad (ConfidentialIDS *ids, FILE *f)
 * \brief load ids's informations from the IDS_FILE
 * \param ids output IDS to load
 * \param f file descriptor to the input file (IDS_FILE)
 * \return status code for this operation.
 *
*/
int idsLoad (ConfidentialIDS * ids, FILE * f);


/** \fn int allIDSLoad (ConfidentialIDS **table, int *size)
 * \brief load a table of IDS from the IDS_FILE
 * \param table output IDS table to load
 * \param size size of this table
 * \return status code for this operation.
 *
*/
int allIDSLoad (ConfidentialIDS ** table, int * size);


/** \fn int allIDSSave (ConfidentialIDS **table, int *size)
 * \brief save all the IDS table to the IDS_FILE
 * \param table ptr to the IDS table to save
 * \param size size of this table
 * \return status code for this operation.
 *
*/
int allIDSSave (ConfidentialIDS ** table, int * size);


/** \fn int idsInTable (char login[USERACCOUNT_LOGIN_LENGTH], char password[USERACCOUNT_PASSWORD_LENGTH], ConfidentialIDS *table, int size, long int *id)
 * \brief test if the given login and password are in the IDS table
 * \param login login string to test
 * \param password password string to test
 * \param table the input IDS table
 * \param size size of this table
 * \param ptrIDS pointer to the matching IDS
 * \return status code for this operation.
 *
*/
int idsInTable (char login[USERACCOUNT_LOGIN_LENGTH], char password[USERACCOUNT_PASSWORD_LENGTH], ConfidentialIDS * table, int size, ConfidentialIDS * ptrIDS);


/** \fn int objLoad (ObjectBid *obj, FILE* f)
 * \brief test if the data's size given match to an ObjectBid var size
 * \param size data to test size
 * \return status code for this operation.
 *
*/
int isObjectBid (int size);


/** \fn int isObjectBidTable (int size)
 * \brief test if the data's size given match to an ObjectBid table size
 * \param size data to test size
 * \return status code for this operation.
 *
*/
int isObjectBidTable (int size);


/** \fn int isAccountUser (int size)
 * \brief test if the data's size given match to an UserAccount var size
 * \param size data to test size
 * \return status code for this operation.
 *
*/
int isAccountUser (int size);


/** \fn long int getCurrentTime()
 * \brief returns  the  time  as  the  number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
 * \return time  as  the  number of seconds since the Epoch, 1970-01-01 00:00:00 +0000 (UTC).
 *
*/
long int getCurrentTime();


/** \fn int isFinishObjectBid(ObjectBid * object)
 * \brief test if an ObjectBid is finished or not, checking his time value.
 * \param object the ObjectBid to test
 * \return status code for this operation.
 *
*/
int isFinishObjectBid(ObjectBid * object);


/** \fn int removeObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object)
 * \brief remove an ObjectBid to an ObjectBid table.
 * \param table the ObjectBid table to purge of one ObjectBid
 * \param size size of this table
 * \param object the ObjectBid to purge from this table
 * \return status code for this operation.
 *
*/
int removeObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object);


/** \fn int addObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object)
 * \brief add an ObjectBid to an ObjectBid table.
 * \param table the ObjectBid table to append of one ObjectBid
 * \param size size of this table
 * \param object the ObjectBid to add into this table
 * \return status code for this operation.
 *
*/
int addObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object);


/** \fn int removeUserAccountInTable(UserAccount ** table, int * size, UserAccount * object)
 * \brief remove an UserAccount to an UserAccount table.
 * \param table the UserAccount table to purge of one UserAccount
 * \param size size of this table
 * \param user the UserAccount to purge from this table
 * \return status code for this operation.
 *
*/
int removeUserAccountInTable(UserAccount ** table, int * size, UserAccount * user);


/** \fn int addUserAccountInTable(UserAccount ** table, int * size, UserAccount * user, ConfidentialIDS ** IDS, int * nbIDS)
 * \brief add an UserAccount to an UserAccount table.
 * \param table the UserAccount table to append of one UserAccount
 * \param size size of this table
 * \param user the UserAccount to add into this table
 * \param IDS the ConfidentialIDS table to append UserAccount IDS
 * \param nbIDS the UserAccount IDS to add to this table
 * \return status code for this operation.
 *
*/
int addUserAccountInTable(UserAccount ** table, int * size, UserAccount * user, ConfidentialIDS ** IDS, int * nbIDS);


/** \fn int searchObjectBidInTable(ObjectBid * table, int size, ObjectBid * object, ObjectBid * ptrObject)
 * \brief search by name a matching ObjectBid
 * \param table the ObjectBid table to search in
 * \param size size of this table
 * \param object the ObjectBid to search
 * \param ptrObject pointer to a matching ObjectBid found
 * \return status code for this operation.
 *
*/
int searchObjectBidInTable(ObjectBid * table, int size, ObjectBid * object, ObjectBid * ptrObject);

#endif
