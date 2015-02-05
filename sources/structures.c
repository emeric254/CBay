#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"


/* videBuffer.
*/
void videBuffer()
{
    char buffer = fgetc(stdin);
    while(buffer != '\n' && buffer != EOF)
    {
        buffer = fgetc(stdin);
    }
}


/* saisieChar
 */
char saisieChar()
{
    char temp = fgetc(stdin);
    while(temp == '\n' || temp == EOF)
    {
        temp = fgetc(stdin);
    }

    return temp;
}


/* saisieUtilisateur.
*/
void saisieUtilisateur(CONTENT_TYPE_USERACCOUNT_NAME * account)
{
    int validInput = FALSE;
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
        account->type = saisieChar();
        CLEAR();
        switch(account->type)
        {
            case ACCOUNT_TYPE_ADMIN:
                validInput = TRUE;
                break;
            case ACCOUNT_TYPE_VENDOR:
                validInput = TRUE;
                break;
            case ACCOUNT_TYPE_USER:
                validInput = TRUE;
                break;
            default:
                validInput = FALSE;
                printf("Input error, please make a correct choice !\n");
                break;
        }
    }while(validInput);

    CLEAR();

    printf("Enter your name\n");
    fgets(account->name,USERACCOUNT_NAME_LENGTH,stdin);
    if(strlen(account->name)<USERACCOUNT_NAME_LENGTH-1)
        account->name[strlen(account->name)] = '\0';
    videBuffer();
    CLEAR();

    printf("Enter your lastname\n");
    fgets(account->lastname,USERACCOUNT_LASTNAME_LENGTH,stdin);
    if(strlen(account->lastname)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->lastname[strlen(account->lastname)] = '\0';
    videBuffer();
    CLEAR();

    printf("Enter your adress\n");
    fgets(account->adress,USERACCOUNT_ADRESS_LENGTH,stdin);
    if(strlen(account->adress)<USERACCOUNT_LASTNAME_LENGTH-1)
        account->adress[strlen(account->adress)] = '\0';
    videBuffer();
    CLEAR();

    do
    {
        printf("Enter your mail\n");
        fgets(account->mail,USERACCOUNT_MAIL_LENGTH,stdin);
        if(strlen(account->mail)<USERACCOUNT_MAIL_LENGTH-1)
            account->mail[strlen(account->mail)] = '\0';
        videBuffer();
    }while(!verifMail(account->mail,strlen(account->mail)));
    CLEAR();

}


/* saisieVente.
*/
void saisieVente(CONTENT_TYPE_OBJECTBID_NAME * bid)
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
    videBuffer();
    CLEAR();

    printf("Enter the bid base price\n");
    fscanf(stdin,"%f",&(bid->basePrice));
    videBuffer();
    CLEAR();

    printf("Enter the bid description\n");
    fgets(bid->description,OBJECTBID_DESCRIPTION_LENGTH,stdin);
    if(strlen(bid->description)<OBJECTBID_DESCRIPTION_LENGTH-1)
        bid->description[strlen(bid->description)] = '\0';
    videBuffer();
    CLEAR();

    printf("Enter the bid adress\n");
    fgets(bid->adress,OBJECTBID_ADRESS_LENGTH,stdin);
    if(strlen(bid->adress)<OBJECTBID_ADRESS_LENGTH-1)
        bid->adress[strlen(bid->adress)] = '\0';
    videBuffer();
    CLEAR();
}


/* verifMail.
*/
int verifMail(char *mail, int taille)
{
    if(mail == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTER);
    }
    int i = 0;
    int arobase = 0 ;
    // test '@'
    for(i=0;i<taille;i++)
        if((mail[i] = '@'))
            arobase ++;
    //

    return (arobase == 1)? TRUE : FALSE;
}


/* accSave.
*/
int accSave(CONTENT_TYPE_USERACCOUNT_NAME user, FILE* f)
{
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(&user,sizeof(CONTENT_TYPE_USERACCOUNT_NAME),1,f);
    return SUCESS;
}


/* accLoad.
*/
int accLoad(CONTENT_TYPE_USERACCOUNT_NAME *user, FILE* f)
{
    //@TODO if fread SUCESS else ERROR_READING
    fread(&user,sizeof(CONTENT_TYPE_USERACCOUNT_NAME),1,f);
    return SUCESS;
}


/* allAccSave.
 */
int allAccSave (CONTENT_TYPE_USERACCOUNT_NAME *table, int size)
{
    FILE *f = fopen(ACC_FILE,"wb");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCESS else ERROR_READING
    fwrite(table,sizeof(CONTENT_TYPE_USERACCOUNT_NAME),size,f);
    fclose(f);
    return SUCESS;
}


/* allAccLoad.
 */
int allAccLoad (CONTENT_TYPE_USERACCOUNT_NAME **table, int * size)
{
    CONTENT_TYPE_USERACCOUNT_NAME *ptr = NULL;
    CONTENT_TYPE_USERACCOUNT_NAME *temp;
    int nbr = 0;
    int state;
    FILE *f = fopen(ACC_FILE,"rb");
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;
    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(CONTENT_TYPE_USERACCOUNT_NAME));
    if (temp == NULL)
        return ERROR_POINTER;

    while( ( state = accLoad(temp, f) ) == SUCESS)
    {
        nbr++; // one more account to load

        ptr = *table; // save the actual content
        // make a table which is bigger
        *table = NULL;
        *table = realloc(*table, nbr*sizeof(CONTENT_TYPE_USERACCOUNT_NAME));

        if (*table == NULL)
        {
            free(ptr);
            return ERROR_POINTER;
        }

        // add the new element
        (*table)[nbr-1] = *temp;

        ptr = NULL;
        temp = NULL;
        temp = malloc(sizeof(CONTENT_TYPE_USERACCOUNT_NAME));

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
int objSave(CONTENT_TYPE_OBJECTBID_NAME obj, FILE* f)
{
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(&obj,sizeof(CONTENT_TYPE_OBJECTBID_NAME),1,f);
    return SUCESS;
}


/* objLoad.
*/
int objLoad(CONTENT_TYPE_OBJECTBID_NAME *obj, FILE* f)
{
    //@TODO if fread SUCESS else ERROR_READING
    fread(&obj,sizeof(CONTENT_TYPE_OBJECTBID_NAME),1,f);
    return SUCESS;
}


/* allObjSave.
 */
int allObjSave (CONTENT_TYPE_OBJECTBID_NAME *table, int size)
{
    FILE *f = fopen(OBJ_FILE,"wb");
    if ( f == NULL )
        return(ERROR_OPENING);
    //@TODO if fwrite SUCESS else ERROR_WRITING
    fwrite(table,sizeof(CONTENT_TYPE_OBJECTBID_NAME),size,f);
    fclose(f);
    return SUCESS;
}


/* allObjLoad.
 */
int allObjLoad (CONTENT_TYPE_OBJECTBID_NAME **table, int *size)
{
    // the function allAccLoad works the same way

    CONTENT_TYPE_OBJECTBID_NAME *ptr = NULL;
    CONTENT_TYPE_OBJECTBID_NAME *temp;
    int nbr = 0;
    int state;
    FILE* f = fopen(OBJ_FILE,"rb") ;
    if ( f == NULL )
        return(ERROR_OPENING);

    // clean the actual table
    free(*table);
    *table=NULL;
    // create a space for a new element
    temp = NULL;
    temp = malloc(sizeof(CONTENT_TYPE_OBJECTBID_NAME));
    if (temp == NULL)
        return ERROR_POINTER;

    while( ( state = objLoad(temp, f) ) == SUCESS)
    {
        nbr++; // one more object to load

        ptr = *table; // save the actual content
        // make a table which is bigger
        *table = NULL;
        *table = realloc(*table, nbr*sizeof(CONTENT_TYPE_OBJECTBID_NAME));

        if (*table == NULL)
        {
            free(ptr);
            return ERROR_POINTER;
        }

        // add the new element
        (*table)[nbr-1] = *temp;

        ptr = NULL;
        temp = NULL;
        temp = malloc(sizeof(CONTENT_TYPE_OBJECTBID_NAME));

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
