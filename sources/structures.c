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

    account->IDS.id=-1;

    do
    {
        // type choice
        printf("Choice your account type\n");
        printf("%c -> %s\n",ACCOUNT_TYPE_ADMIN,ACCOUNT_LABEL_ADMIN);
        printf("%c -> %s\n",ACCOUNT_TYPE_VENDOR,ACCOUNT_LABEL_VENDOR);
        printf("%c -> %s\n",ACCOUNT_TYPE_USER,ACCOUNT_LABEL_USER);
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
    }while( ! goodInput);

    CLEAR();

    cleanBuffer();

    printf("Enter your name\n");
    fgets(account->name,USERACCOUNT_NAME_LENGTH-1,stdin);
    if(account->name[strlen(account->name)-1]=='\n')
        account->name[strlen(account->name)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    printf("Enter your lastname\n");
    fgets(account->lastname,USERACCOUNT_LASTNAME_LENGTH-1,stdin);
    if(account->lastname[strlen(account->lastname)-1]=='\n')
        account->lastname[strlen(account->lastname)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    printf("Enter your adress\n");
    fgets(account->adress,USERACCOUNT_ADRESS_LENGTH-1,stdin);
    if(account->adress[strlen(account->adress)-1]=='\n')
        account->adress[strlen(account->adress)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    do
    {
        printf("Enter your mail\n");
        fgets(account->mail,USERACCOUNT_MAIL_LENGTH-1,stdin);
        if(account->mail[strlen(account->mail)-1]=='\n')
            account->mail[strlen(account->mail)-1] = '\0';
        else
            cleanBuffer();
    }while(!mailCheck(account->mail,strlen(account->mail)));
    CLEAR();


    printf("Enter your login\n");
    fgets(account->IDS.login,USERACCOUNT_LOGIN_LENGTH,stdin);
    if(account->IDS.login[strlen(account->IDS.login)-1]=='\n')
        account->IDS.login[strlen(account->IDS.login)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    printf("Enter your password\n");
    fgets(account->IDS.password,USERACCOUNT_PASSWORD_LENGTH,stdin);
    if(account->IDS.password[strlen(account->IDS.password)-1]=='\n')
        account->IDS.password[strlen(account->IDS.password)-1] = '\0';
    else
        cleanBuffer();
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
    if(bid->name[strlen(bid->name)-1]=='\n')
        bid->name[strlen(bid->name)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    printf("Enter the bid base price\n");
    fscanf(stdin,"%f",&(bid->basePrice));
    CLEAR();

    printf("Enter the bid description\n");
    fgets(bid->description,OBJECTBID_DESCRIPTION_LENGTH,stdin);
    if(bid->name[strlen(bid->name)-1]=='\n')
        bid->name[strlen(bid->name)-1] = '\0';
    else
        cleanBuffer();
    CLEAR();

    printf("Enter the bid adress\n");
    fgets(bid->adress,OBJECTBID_ADRESS_LENGTH,stdin);
    if(bid->name[strlen(bid->name)-1]=='\n')
        bid->name[strlen(bid->name)-1] = '\0';
    else
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
        if((mail[i] == '@'))
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
        if ( user->IDS.id == table[i].IDS.id )
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
int isObjectBid (char ** data, int size)
{
    if ( strcmp(&(*data[size-3]),";\n") == 0  && *data[size-4] != ';')
    {
        //
    }

    return (size == sizeof(ObjectBid)) ? TRUE : FALSE;
}


/* isObjectBidTable.
 *
 */
int isObjectBidTable (char ** data, int size)
{
    ObjectBid * ptrObject = NULL;
/*
    if ( strcmp(&(*data[size-4]),";;\n") == 0)
    {
        int i = 4;
        ptrUser = malloc(sizeof(UserAccount));
        ptrUser->type = *data[i++];

        memcpy(ptrObject->IDS.id, &(*data[j]), sizeof(long int));
        j+=sizeof(long int);

        sscanf(&(*data[j]), "%s;", ptrObject->IDS.login);
        j+=strlen(ptrUser->IDS.login)+1;

        sscanf(&(*data[j]), "%s;", ptrObject->IDS.password);
        j+=strlen(ptrUser->IDS.password)+1;

        sscanf(&(*data[j]), "%s;", ptrObject->name);
        j+=strlen(ptrUser->name)+1;

        sscanf(&(*data[j]), "%s;", ptrObject->lastname);
        j+=strlen(ptrUser->lastname)+1;

        sscanf(&(*data[j]), "%s;", ptrObject->adress);
        j+=strlen(ptrUser->adress)+1;

        sscanf(&(*data[j]), "%s;", ptrObject->mail);
        j+=strlen(ptrUser->mail)+1;

        free(*data);
        if(*data!=NULL)
            return ERROR_POINTER;
        *data=ptrObject;
    }
*/
    return (ptrObject == NULL) ? TRUE : FALSE;
}


/* isAccountUser.
 *
 */
int isAccountUser (char ** data, int size)
{
    UserAccount * ptrUser = NULL;
    if ( strcmp(&(*data[size-4]),";;\n") == 0)
    {
        int j = 4;
        ptrUser = malloc(sizeof(UserAccount));
        ptrUser->type = *data[j++];

//        memcpy(&(ptrUser->IDS.id), &(*data[j]), sizeof(long int));
        // ou
        ptrUser->IDS.id = *data[j];
        j+=sizeof(long int);

        sscanf(&(*data[j]), "%s;", ptrUser->IDS.login);
        j+=strlen(ptrUser->IDS.login)+1;

        sscanf(&(*data[j]), "%s;", ptrUser->IDS.password);
        j+=strlen(ptrUser->IDS.password)+1;

        sscanf(&(*data[j]), "%s;", ptrUser->name);
        j+=strlen(ptrUser->name)+1;

        sscanf(&(*data[j]), "%s;", ptrUser->lastname);
        j+=strlen(ptrUser->lastname)+1;

        sscanf(&(*data[j]), "%s;", ptrUser->adress);
        j+=strlen(ptrUser->adress)+1;

        sscanf(&(*data[j]), "%s;", ptrUser->mail);
        j+=strlen(ptrUser->mail)+1;

        free(*data);
        if(*data!=NULL)
            return ERROR_POINTER;
        *data=(char*)ptrUser;
    }

    return (ptrUser == NULL) ? TRUE : FALSE;
}


long int getCurrentTime()
{
    return (long int)time(NULL);
}


int isFinishObjectBid(ObjectBid * object)
{
    return (object->endTime <= getCurrentTime()) ? TRUE : FALSE ;
}


int removeObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object)
{
    int i = 0;
    int j = 0;
    ObjectBid * newTable = NULL;

    newTable = malloc((*size-1)*sizeof(ObjectBid));

    if(newTable == NULL)
        return ERROR_POINTER;

    for(i=0; i < *size-1; i++)
    {
        if((*table[i]).id != object->id)
        {
            newTable[j++] = *table[i];
        }
    }

    if(j != (i-1))
        return ERROR_POINTER;

    free(*table);
    table = &newTable;

    return SUCCESS;
}


int addObjectBidInTable(ObjectBid ** table, int * size, ObjectBid * object)
{
    int i = 0;
    ObjectBid * newTable = NULL;

    *size += 1;
    newTable = malloc((*size)*sizeof(ObjectBid));

    if(newTable == NULL)
        return ERROR_POINTER;

    for(i=0; i < *size -1 ; i++)
    {
        newTable[i] = *table[i];
    }

    newTable[*size -1] = *object;

    free(*table);
    table = &newTable;

    return SUCCESS;
}


int removeUserAccountInTable(UserAccount ** table, int * size, UserAccount * user)
{
    int i = 0;
    int j = 0;
    UserAccount * newTable = NULL;

    newTable = malloc((*size-1)*sizeof(UserAccount));

    if(newTable == NULL)
        return ERROR_POINTER;

    for(i=0; i < *size-1; i++)
    {
        if((*table[i]).IDS.id != user->IDS.id)
        {
            newTable[j++] = *table[i];
        }
    }

    if(j != (i-1))
        return ERROR_POINTER;

    free(*table);
    table = &newTable;

    return SUCCESS;
}

int addIDSInTable(ConfidentialIDS ** table, int * size, ConfidentialIDS toAdd)
{
    int i = 0;
    ConfidentialIDS * newTable = NULL;

    *size += 1;
    newTable = malloc((*size)*sizeof(ConfidentialIDS));

    if(newTable == NULL)
        return ERROR_POINTER;

    for(i=0; i < *size -1 ; i++)
    {
        newTable[i] = *table[i];
    }

    newTable[*size -1] = toAdd;

    free(*table);
    table = &newTable;

    return SUCCESS;
}


int addUserAccountInTable(UserAccount ** table, int * size, UserAccount * user, ConfidentialIDS ** IDS, int * nbIDS)
{
    int i = 0;
    UserAccount * newTable = NULL;

    *size += 1;
    newTable = malloc((*size)*sizeof(UserAccount));

    if(newTable == NULL)
        return ERROR_POINTER;

    for(i=0; i < *size -1 ; i++)
    {
        newTable[i] = *table[i];
    }

    newTable[*size -1] = *user;

    free(*table);
    table = &newTable;

    return addIDSInTable(IDS, nbIDS, user->IDS);
}


int searchObjectBidInTable(ObjectBid * table, int size, ObjectBid * object, ObjectBid * ptrObject)
{
    int i = 0;

    if(ptrObject!=NULL)
        ptrObject = NULL;

    for(i=0; i < size-1; i++)
    {
        if((table[i]).name != object->name)
        {
            ptrObject = &(table[i]);
            return TRUE;
        }
    }

    return FALSE;
}
