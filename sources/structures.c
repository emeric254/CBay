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
        fprintf(stderr,"null pointer");
        return ERREUR_POINTEUR;
    }

    do
    {
        // type choice
        printf("Choice your account type\n");
        printf("%c - %s\n",ACCOUNT_TYPE_ADMIN,ACCOUNT_LABEL_ADMIN);
        printf("%c - %s\n",ACCOUNT_TYPE_VENDOR,ACCOUNT_LABEL_VENDOR);
        printf("%c - %s\n",ACCOUNT_TYPE_USER,ACCOUNT_LABEL_USER);
        account->type = saisieChar();
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
                break;
        }
    }while(validInput);




}


/* saisieVente.
*/
void saisieVente(ObjectBid * bid)
{
    if(bid == NULL)
    {
        fprintf(stderr,"null pointer");
        return ERREUR_POINTEUR;
    }
}


/* verifMail.
*/
int verifMail(char *mail, int taille)
{
    if(mail == NULL)
    {
        fprintf(stderr,"null pointer");
        return ERREUR_POINTEUR;
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
