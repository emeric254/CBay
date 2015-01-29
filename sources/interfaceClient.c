#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
#include "defines.h"
#include "structures.h"


/* menuAccueil
 */
int menuAccueil()
{
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Quitter\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Connexion\n", MENU_CHOICE_MAIN_CONNECTION);
    fprintf(stdout, "\t\t\t\t%d - Creation de compte\n", MENU_CHOICE_MAIN_ACCOUNT_CREATION);
    fprintf(stdout, "\t\t\t\t%d - Poursuivre anonymement\n", MENU_CHOICE_MAIN_ANONYMOUS);
//    videBuffer();
    return saisieChar() - '0';
}


/* menuPrincipal
 */
int menuPrincipal()
{
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Retour\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Liste d'objets\n", MENU_CHOICE_MAIN_LIST);
    fprintf(stdout, "\t\t\t\t%d - Recherche d'objet(s) par mot clef\n", MENU_CHOICE_MAIN_SEARCH);
//    videBuffer();
    return saisieChar() - '0';
}
