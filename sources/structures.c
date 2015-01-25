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
}


/* saisieVente.
*/
void saisieVente(ObjectBid * bid)
{
}


/* verifMail.
*/
int verifMail(char *mail, int taille)
{
    int i = 0;
    int arobase = 0 ;
    // test '@'
    for(i=0;i<taille;i++)
        if(mail[i] = '@')
            arobase ++;
    //

    return (arobase == 1)? TRUE : FALSE;
}

int accSave (UserAccount user)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"ab"))==NULL)
        return(ERREUR_OUVERTURE);
    fwrite(&user,sizeof(UserAccount),1,f);
    fclose(f);
    return SUCCESS;
}

int accLoad (UserAccount *user)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"rb"))==NULL)
        return(ERREUR_OUVERTURE);
    fread(&user,sizeof(UserAccount),1,f);
    fclose(f);
    return SUCCESS;
}

int objSave (ObjectBid obj)
{
    FILE* f;
    if((f=fopen(OBJ_FILE,"rb"))==NULL)
        return(ERREUR_OUVERTURE);
    fread(&obj,sizeof(ObjectBid),1,f);
    fclose(f);
    return SUCCESS;
}

int objLoad (ObjectBid *obj)
{
    FILE* f;
    if((f=fopen(ACC_FILE,"rb"))==NULL)
        return(ERREUR_OUVERTURE);
    fread(&obj,sizeof(ObjectBid),1,f);
    fclose(f);
    return SUCCESS;
}
