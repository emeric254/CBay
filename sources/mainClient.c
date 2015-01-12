#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "client.h"


int main(void)
{
    int choixMenu = menuAccueil();
    do
    {
        CLEAR();
        printf("\n\n\t\t\t\t\t\t\t%d\n\n",choixMenu);
        switch(choixMenu)
        {
            case CHOIX_MENU_QUITTER:
                printf("\n\t\t Merci d'avoir utiliser BEEP !\n\n");
                break;
            case CHOIX_MENU_ACCUEIL_CONNEXION:
                // if(connexion) menuConnexion();
                break;
            case CHOIX_MENU_ACCUEIL_CREATIONCOMPTE:
                printf("\t\t\tBienvenue sur l'utilitaire de création de compte\n");
                // menuCreationCompte();
                break;
            case CHOIX_MENU_ACCUEIL_ANONYME:
                choixMenu = menuPrincipal();
                break;
            default:
                printf("\n\t\t --- Veuillez rentrer un choix correct !\n\n");
                break;
        }

        if(choixMenu)
            choixMenu = menuAccueil();
    }while(choixMenu);

    printf("\nappuyer sur une touche pour quitter\n");
    getc(stdin); // équivaut à une pause
    return 0;
}


/*
int main() {
    char *message = NULL;

    fprintf(stdout,"mainClient !\n");

    if(!InitialisationAvecService(ADR_SERVEUR, PORT_SERVEUR))
    {
        fprintf(stderr,"Erreur d'initialisation !");
        return 1;
    }

    if(Emission("GET / HTTP/1.0\n\n")){
        while (message = Reception()){
            fprintf(stdout,"%s",message);
            free(message);
        }
    }

    Terminaison();

    return 0;
}
*/
