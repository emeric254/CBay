#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"


/* clearBuffer.
*/
void clearBuffer()
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
    clearBuffer();
    CLEAR();

    printf("Enter your lastname\n");
    fgets(account->lastname,USERACCOUNT_LASTNAME_LENGTH,stdin);
    if(strlen(account->lastname)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->lastname[strlen(account->lastname)] = '\0';
    clearBuffer();
    CLEAR();

    printf("Enter your adress\n");
    fgets(account->adress,USERACCOUNT_ADRESS_LENGTH,stdin);
    if(strlen(account->adress)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->adress[strlen(account->adress)] = '\0';
    clearBuffer();
    CLEAR();

    do
    {
        printf("Enter your mail\n");
        fgets(account->mail,USERACCOUNT_MAIL_LENGTH,stdin);
        if(strlen(account->mail)<USERACCOUNT_MAIL_LENGTH-1)
            account->mail[strlen(account->mail)] = '\0';
        clearBuffer();
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
    clearBuffer();
    CLEAR();

    printf("Enter the bid base price\n");
    fscanf(stdin,"%f",&(bid->basePrice));
    clearBuffer();
    CLEAR();

    printf("Enter the bid description\n");
    fgets(bid->description,OBJECTBID_DESCRIPTION_LENGTH,stdin);
    if(strlen(bid->description)<OBJECTBID_DESCRIPTION_LENGTH-1)
        bid->description[strlen(bid->description)] = '\0';
    clearBuffer();
    CLEAR();

    printf("Enter the bid adress\n");
    fgets(bid->adress,OBJECTBID_ADRESS_LENGTH,stdin);
    if(strlen(bid->adress)<OBJECTBID_ADRESS_LENGTH-1)
        bid->adress[strlen(bid->adress)] = '\0';
    clearBuffer();
    CLEAR();
}


/* mailCheck.
*/
int mailCheck(char *mail, int taille)
{
    if(mail == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTER);
    }
    int i = 0;
    int arobase = 0 ;
    // count how many '@'
    for(i=0;i<taille;i++)
        if((mail[i] = '@'))
            arobase ++;
    //only one '@' in a valide mail adress

    return (arobase == 1)? TRUE : FALSE;
}


/* accSave.
*/
int accSave(UserAccount user, FILE* f)
{
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(&user,sizeof(UserAccount),1,f);
    return SUCESS;
}


/* accLoad.
*/
int accLoad(UserAccount *user, FILE* f)
{
    //@TODO if fread SUCESS else ERROR_READING
    fread(&user,sizeof(UserAccount),1,f);
    return SUCESS;
}


/* userInTable.
 */
int userInTable (UserAccount *user, UserAccount *table, int size, long int *id)
{
    int i = 0;
    int find = FALSE;
    while(find == FALSE && i < size)
    {
        if ( user->id == table[i].id )
            find = TRUE;
        i++;
    }
    if (id != NULL)
        *id = (find) ? table[i].id : -1 ; // if find : id = id ; else id = -1;
    return find;
}


/* allAccSave.
 */
int allAccSave (UserAccount *table, int size)
{
    FILE *f = fopen(ACC_FILE,"wb");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCESS else ERROR_READING

    fwrite(table, sizeof(UserAccount), (size_t)size, f);

    fclose(f);
    return SUCESS;
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
    FILE *f = fopen(ACC_FILE,"rb");
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
    while( ( state = accLoad(temp, f) ) == SUCESS)
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
    return SUCESS;
}


/* objSave.
*/
int objSave(ObjectBid obj, FILE* f)
{
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(&obj,sizeof(ObjectBid),1,f);
    return SUCESS;
}


/* objLoad.
*/
int objLoad(ObjectBid *obj, FILE* f)
{
    //@TODO if fread SUCESS else ERROR_READING
    fread(&obj,sizeof(ObjectBid),1,f);
    return SUCESS;
}


/* objInTable.
 */
int objInTable (ObjectBid *obj, ObjectBid *table, int size, long int *id)
{
    int i = 0;
    int find = FALSE;
    while(find == FALSE && i < size)
    {
        if ( obj->id == table[i].id )
            find = TRUE;
        i++;
    }
    if (id != NULL)
        *id = (find) ? table[i].id : -1 ; // if find : id = id ; else id = -1;
    return find;
}


/* allObjSave.
 */
int allObjSave (ObjectBid *table, int size)
{
    FILE *f = fopen(OBJ_FILE,"wb");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCESS else ERROR_WRITING

    fwrite(table, sizeof(ObjectBid), (size_t)size, f);

    fclose(f);
    return SUCESS;
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
    FILE* f = fopen(OBJ_FILE,"rb") ;
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;

    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(ObjectBid));
    if (temp == NULL)
        return ERROR_POINTER;

    // while elements can be readed
    while( ( state = objLoad(temp, f) ) == SUCESS)
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
    return SUCESS;
}


/* idsLoad.
 */
int idsLoad (ConfidentialIDS *ids, FILE *f)
{
    //@TODO if fread SUCESS else ERROR_READING
    fread(&ids,sizeof(ConfidentialIDS),1,f);
    return SUCESS;
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
    FILE* f = fopen(IDS_FILE,"rb") ;
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
    while( ( state = idsLoad(temp, f) ) == SUCESS)
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
    return SUCESS;
}


/* allIDSLoad.
 */
int allIDSSave (ConfidentialIDS **table, int *size)
{
    FILE *f = fopen(IDS_FILE,"wb");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(table, sizeof(ConfidentialIDS), (size_t)size, f);
    fclose(f);
    return SUCESS;
}


/* idsInTable.
 */
int idsInTable (char login[USERACCOUNT_LOGIN_LENGTH], char password[USERACCOUNT_PASSWORD_LENGTH], ConfidentialIDS *table, int size, long int *id)
{
    int i = 0;
    int find = FALSE;
    while(find == FALSE && i < size)
    {
        if ( !strcmp(login,table[i].login) && !strcmp(password,table[i].password) )
            find = TRUE;
        i++;
    }
    if (id != NULL)
        *id = (find) ? table[i].id : -1 ; // if find : id = id ; else id = -1;
    return find;
}


/* file_length.
*/
size_t file_length(char *filename){
    int length = -1;
    FILE * file = fopen(filename,"r");
    if (file!=NULL)
    {
        fseek(file,0,SEEK_END);
        length = ftell(file);
        fclose(file);
    }
    fprintf(ERROROUTPUT,"error unknown file : (%s)\n",filename);
    return length; // -1 if unknown file, 0 if empty, otherwise it return the file length
}
