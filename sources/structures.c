#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"


/* cleanBuffer.
*/
void cleanBuffer()
{
    char buffer = fgetc(stdin);
    while(buffer != '\n' && buffer != EOF)
    {
        buffer = fgetc(stdin);
    }
}


/* getAChar
 */
char getAChar()
{
    char temp = fgetc(stdin);
    while(temp == '\n' || temp == EOF)
    {
        temp = fgetc(stdin);
    }

    return temp;
}


/* userInputUserAccount.
*/
void userInputUserAccount(UserAccount * account)
{
    int goodInput = FALSE;
    if(account == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTER);
    }

    do
    {
        // type choice
        printf("Choice your account type\n");
        printf("%c - %s\n",ACCOUNT_TYPE_ADMIN,ACCOUNT_LABEL_ADMIN);
        printf("%c - %s\n",ACCOUNT_TYPE_VENDOR,ACCOUNT_LABEL_VENDOR);
        printf("%c - %s\n",ACCOUNT_TYPE_USER,ACCOUNT_LABEL_USER);
        account->type = getAChar();
        CLEAR();
        switch(account->type)
        {
            case ACCOUNT_TYPE_ADMIN:
                goodInput = TRUE;
                break;
            case ACCOUNT_TYPE_VENDOR:
                goodInput = TRUE;
                break;
            case ACCOUNT_TYPE_USER:
                goodInput = TRUE;
                break;
            default:
                goodInput = FALSE;
                printf("Input error, please make a correct choice !\n");
                break;
        }
    }while(goodInput);

    CLEAR();

    printf("Enter your name\n");
    fgets(account->name,USERACCOUNT_NAME_LENGTH,stdin);
    if(strlen(account->name)<USERACCOUNT_NAME_LENGTH-1)
        account->name[strlen(account->name)] = '\0';
    cleanBuffer();
    CLEAR();

    printf("Enter your lastname\n");
    fgets(account->lastname,USERACCOUNT_LASTNAME_LENGTH,stdin);
    if(strlen(account->lastname)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->lastname[strlen(account->lastname)] = '\0';
    cleanBuffer();
    CLEAR();

    printf("Enter your adress\n");
    fgets(account->adress,USERACCOUNT_ADRESS_LENGTH,stdin);
    if(strlen(account->adress)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->adress[strlen(account->adress)] = '\0';
    cleanBuffer();
    CLEAR();

    do
    {
        printf("Enter your mail\n");
        fgets(account->mail,USERACCOUNT_MAIL_LENGTH,stdin);
        if(strlen(account->mail)<USERACCOUNT_MAIL_LENGTH-1)
            account->mail[strlen(account->mail)] = '\0';
        cleanBuffer();
    }while(!mailCheck(account->mail,strlen(account->mail)));
    CLEAR();

}


/* userInputObjectBid.
*/
void userInputObjectBid(ObjectBid * bid)
{
    if(bid == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTER);
    }

    printf("Enter the bid name\n");
    fgets(bid->name,OBJECTBID_NAME_LENGTH,stdin);
    if(strlen(bid->name)<OBJECTBID_NAME_LENGTH-1)
        bid->adress[strlen(bid->name)] = '\0';
    cleanBuffer();
    CLEAR();

    printf("Enter the bid base price\n");
    fscanf(stdin,"%f",&(bid->basePrice));
    cleanBuffer();
    CLEAR();

    printf("Enter the bid description\n");
    fgets(bid->description,OBJECTBID_DESCRIPTION_LENGTH,stdin);
    if(strlen(bid->description)<OBJECTBID_DESCRIPTION_LENGTH-1)
        bid->description[strlen(bid->description)] = '\0';
    cleanBuffer();
    CLEAR();

    printf("Enter the bid adress\n");
    fgets(bid->adress,OBJECTBID_ADRESS_LENGTH,stdin);
    if(strlen(bid->adress)<OBJECTBID_ADRESS_LENGTH-1)
        bid->adress[strlen(bid->adress)] = '\0';
    cleanBuffer();
    CLEAR();
}


/* mailCheck.
*/
int mailCheck(char *mail, int length)
{
    if(mail == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTER);
    }
    int i = 0;
    int arobase = 0 ;
    // count how many '@'
    for(i=0;i<length;i++)
        if((mail[i] = '@'))
            arobase ++;
    //only one '@' in a valide mail adress

    return (arobase == 1)? TRUE : FALSE;
}


/* accSave.
*/
int accSave(UserAccount user, FILE* f)
{
    //@TODO if fwrite SUCCESS else ERROR_WRITING
    fwrite(&user,sizeof(UserAccount),1,f);
    return SUCCESS;
}


/* accLoad.
*/
int accLoad(UserAccount *user, FILE* f)
{
    //@TODO if fread SUCCESS else ERROR_READING
    fread(&user,sizeof(UserAccount),1,f);
    return SUCCESS;
}


/* userInTable.
 */
int userInTable (UserAccount *user, UserAccount *table, int size, UserAccount * ptrAccount)
{
    int i = 0;
    int find = FALSE;

    if(ptrAccount != NULL)
        ptrAccount = NULL;

    while(find == FALSE && i < size)
    {
        if ( user->id == table[i].id )
            find = TRUE;
        i++;
    }

    ptrAccount = (find) ? &table[i] : NULL ;

    return find;
}


/* allAccSave.
 */
int allAccSave (UserAccount *table, int size)
{
    FILE *f = fopen(ACC_FILE,"w+");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCCESS else ERROR_READING
    fwrite(table, sizeof(UserAccount), (size_t)size, f);
    fclose(f);
    return SUCCESS;
}


/* allAccLoad.
 */
int allAccLoad (UserAccount **table, int * size)
{
    UserAccount *ptr = NULL;
    UserAccount *temp;
    int nbr = 0;
    int state;

    // open the file
    FILE *f = fopen(ACC_FILE,"r");
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;

    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(UserAccount));
    if (temp == NULL)
        return ERROR_POINTER;

    // while elements can be readed
    while( ( state = accLoad(temp, f) ) == SUCCESS)
    {
        nbr++; // one more account to load

        ptr = *table; // save the actual content
        // make a table which is bigger
        *table = NULL;
        *table = realloc(*table, nbr*sizeof(UserAccount));

        if (*table == NULL)
        {
            free(ptr);
            return ERROR_POINTER;
        }

        // add the new element
        (*table)[nbr-1] = *temp;

        ptr = NULL;
        temp = NULL;
        temp = malloc(sizeof(UserAccount));

        if (temp == NULL)
        {
            free(*table);
            return ERROR_POINTER;
        }
    }

    free(temp); // clean the unused space
    fclose(f); // close the file
    *size = nbr; // write the size of the table on the output var
    return SUCCESS;
}


/* objSave.
*/
int objSave(ObjectBid obj, FILE* f)
{
    //@TODO if fwrite SUCCESS else ERROR_WRITING
    fwrite(&obj,sizeof(ObjectBid),1,f);
    return SUCCESS;
}


/* objLoad.
*/
int objLoad(ObjectBid *obj, FILE* f)
{
    //@TODO if fread SUCCESS else ERROR_READING
    fread(&obj,sizeof(ObjectBid),1,f);
    return SUCCESS;
}


/* objInTable.
 */
int objInTable (ObjectBid *obj, ObjectBid *table, int size, ObjectBid * ptrObject)
{
    int i = 0;
    int find = FALSE;

    if(ptrObject != NULL)
        ptrObject = NULL;

    while(find == FALSE && i < size)
    {
        if ( obj->id == table[i].id )
            find = TRUE;
        i++;
    }

    ptrObject = (find) ? &table[i] : NULL ;

    return find;
}


/* allObjSave.
 */
int allObjSave (ObjectBid *table, int size)
{
    FILE *f = fopen(OBJ_FILE,"w+");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCCESS else ERROR_WRITING
    fwrite(table, sizeof(ObjectBid), (size_t)size, f);
    fclose(f);
    return SUCCESS;
}


/* allObjLoad.
 */
int allObjLoad (ObjectBid **table, int *size)
{
    // the function allAccLoad works the same way

    ObjectBid *ptr = NULL;
    ObjectBid *temp;
    int nbr = 0;
    int state;

    // open the file
    FILE* f = fopen(OBJ_FILE,"r") ;
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;

    /* @DEBUG */printf("2222\n");

    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(ObjectBid));
    if (temp == NULL)
        return ERROR_POINTER;

    // while elements can be readed
    while( ( state = objLoad(temp, f) ) == SUCCESS)
    {
        nbr++; // one more object to load

        ptr = *table; // save the actual content
        // make a table which is bigger
        *table = NULL;
        *table = realloc(*table, nbr*sizeof(ObjectBid));

        if (*table == NULL)
        {
            free(ptr);
            return ERROR_POINTER;
        }

        // add the new element
        (*table)[nbr-1] = *temp;

        ptr = NULL;
        temp = NULL;
        temp = malloc(sizeof(ObjectBid));

        if (temp == NULL)
        {
            free(*table);
            return ERROR_POINTER;
        }
    }

    free(temp); // clean the unused space
    fclose(f); // close the file
    *size = nbr; // write the size of the table on the output var
    return SUCCESS;
}


/* idsLoad.
 */
int idsLoad (ConfidentialIDS *ids, FILE *f)
{
    //@TODO if fread SUCCESS else ERROR_READING
    fread(&ids,sizeof(ConfidentialIDS),1,f);
    return SUCCESS;
}


/* allIDSLoad.
 */
int allIDSLoad (ConfidentialIDS **table, int *size)
{

    // the function allAccLoad works the same way

    ConfidentialIDS *ptr = NULL;
    ConfidentialIDS *temp;
    int nbr = 0;
    int state;

    // open the file
    FILE* f = fopen(IDS_FILE,"r") ;
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;

    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(ConfidentialIDS));
    if (temp == NULL)
        return ERROR_POINTER;

    // while elements can be readed
    while( ( state = idsLoad(temp, f) ) == SUCCESS)
    {
        nbr++; // one more object to load

        ptr = *table; // save the actual content
        // make a table which is bigger
        *table = NULL;
        *table = realloc(*table, nbr*sizeof(ConfidentialIDS));

        if (*table == NULL)
        {
            free(ptr);
            return ERROR_POINTER;
        }

        // add the new element
        (*table)[nbr-1] = *temp;

        ptr = NULL;
        temp = NULL;
        temp = malloc(sizeof(ConfidentialIDS));

        if (temp == NULL)
        {
            free(*table);
            return ERROR_POINTER;
        }
    }

    free(temp); // clean the unused space
    fclose(f); // close the file
    *size = nbr; // write the size of the table on the output var
    return SUCCESS;
}


/* allIDSLoad.
 */
int allIDSSave (ConfidentialIDS **table, int *size)
{
    FILE *f = fopen(IDS_FILE,"w+");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCCESS else ERROR_WRITING
    fwrite(table, sizeof(ConfidentialIDS), (size_t)size, f);
    fclose(f);
    return SUCCESS;
}


/* idsInTable.
 */
int idsInTable (char login[USERACCOUNT_LOGIN_LENGTH], char password[USERACCOUNT_PASSWORD_LENGTH], ConfidentialIDS *table, int size, ConfidentialIDS * ptrIDS)
{
    int i = 0;
    int find = FALSE;

    if(ptrIDS != NULL)
        ptrIDS = NULL;

    while(find == FALSE && i < size)
    {
        if ( !strcmp(login,table[i].login) && !strcmp(password,table[i].password) )
            find = TRUE;
        i++;
    }

    ptrIDS = (find) ? &table[i] : NULL ;

    return find;
}


/* isObjectBid.
 *
 */
int isObjectBid (int size)
{
    return (size == sizeof(ObjectBid)) ? TRUE : FALSE;
}


/* isObjectBidTable.
 *
 */
int isObjectBidTable (int size)
{
    return ( (size % sizeof(ObjectBid)) == 0) ? TRUE : FALSE;
}


/* isAccountUser.
 *
 */
int isAccountUser (int size)
{
    return (size == sizeof(UserAccount)) ? TRUE : FALSE;
}


long int getCurrentTime()
{
    return (long int)time(NULL);
}


int isFinishObjectBid(ObjectBid * object)
{
    return (object->endTime <= getCurrentTime()) ? TRUE : FALSE ;
}
