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
void saisieUtilisateur(UserAccount * account)
{
    int validInput = FALSE;
    if(account == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTEUR);
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
void saisieVente(ObjectBid * bid)
{
    if(bid == NULL)
    {
        fprintf(ERROROUTPUT,"null pointer");
        exit(ERROR_POINTEUR);
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
        exit(ERROR_POINTEUR);
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

/*
*/
int accSave (UserAccount user)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"ab"))==NULL)
        return(ERROR_OUVERTURE);
    fwrite(&user,sizeof(UserAccount),1,f);
    fclose(f);
    return TRUE;
}

/*
*/
int accLoad (UserAccount *user)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"rb"))==NULL)
        return(ERROR_OUVERTURE);
    fread(&user,sizeof(UserAccount),1,f);
    fclose(f);
    return TRUE;
}

/*
*/
int objSave (ObjectBid obj)
{
    FILE* f;
    if((f=fopen(OBJ_FILE,"rb"))==NULL)
        return(ERROR_OUVERTURE);
    fread(&obj,sizeof(ObjectBid),1,f);
    fclose(f);
    return TRUE;
}

/*
*/
int objLoad (ObjectBid *obj)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"rb"))==NULL)
        return(ERROR_OUVERTURE);
    fread(&obj,sizeof(ObjectBid),1,f);
    fclose(f);
    return TRUE;
}
