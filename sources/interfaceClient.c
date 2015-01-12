#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
#include "defines.h"


/* menuAccueil
 */
int menuAccueil()
{
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Quitter\n", CHOIX_MENU_QUITTER);
    fprintf(stdout, "\t\t\t\t%d - Connexion\n", CHOIX_MENU_ACCUEIL_CONNEXION);
    fprintf(stdout, "\t\t\t\t%d - Creation de compte\n", CHOIX_MENU_ACCUEIL_CREATIONCOMPTE);
    fprintf(stdout, "\t\t\t\t%d - Poursuivre anonymement\n", CHOIX_MENU_ACCUEIL_ANONYME);
//    videBuffer();
    return saisieChar() - '0';
}


/* menuPrincipal
 */
int menuPrincipal()
{
    fprintf(stdout, "\t\t\t\tBIENVENUE SUR BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Retour\n", CHOIX_MENU_QUITTER);
    fprintf(stdout, "\t\t\t\t%d - Liste d'objets\n", CHOIX_MENU_PRINCIPAL_LISTE);
    fprintf(stdout, "\t\t\t\t%d - Recherche d'objet(s) par mot clef\n", CHOIX_MENU_PRINCIPAL_RECHERCHE);
//    videBuffer();
    return saisieChar() - '0';
}
