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
