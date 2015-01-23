#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "structures.h"
#include "interfaceClient.h"
#include "client.h"


int main(void)
{
    // variables
    int choixMenu; // le choix fait par l'utilisateur

    // on fais le ménage sur l'écran pour commencer
    CLEAR();

    // début de la boucle "interface"
    while ( CHOIX_MENU_QUITTER != ( choixMenu = menuAccueil() ) )
    {
        CLEAR();

        // debug
        printf("[%d]\n",choixMenu);

        switch(choixMenu)
        {
            case CHOIX_MENU_ACCUEIL_CONNEXION:
                // pour l'instant afficher ca
                printf("\t\t\tBienvenue sur le menu de connexion\n");

                /*
                while(CHOIX_MENU_QUITTER != (choixMenu = menuConnexion()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case CHOIX_MENU_QUITTER:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t\t --- Veuillez rentrer un choix correct !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case CHOIX_MENU_ACCUEIL_CREATIONCOMPTE:
                // pour l'instant afficher ca
                printf("\t\t\tBienvenue sur l'utilitaire de création de compte\n");

                /*
                while(CHOIX_MENU_QUITTER != (choixMenu = menuCreationCompte()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case CHOIX_MENU_QUITTER:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t\t --- Veuillez rentrer un choix correct !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case CHOIX_MENU_ACCUEIL_ANONYME:
                while(CHOIX_MENU_QUITTER != (choixMenu = menuPrincipal()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case CHOIX_MENU_QUITTER:
                            // rien à faire car retour demandé
                            break;

                        case CHOIX_MENU_PRINCIPAL_LISTE:
                            printf("\n\t\t --- WIP >> liste\n\n");
                            break;

                        case CHOIX_MENU_PRINCIPAL_RECHERCHE:
                            printf("\n\t\t --- WIP >> recherche\n\n");
                            break;

                        default:
                            printf("\n\t\t --- Veuillez rentrer un choix correct !\n\n");
                            break;
                    }
                }
                CLEAR();
                break;

            default:
                printf("\n\t\t --- Veuillez rentrer un choix correct !\n\n");
                break;
        }
    }

    CLEAR();
    printf("\n\t\t Merci d'avoir utiliser BEEP !\n\n");

/*
    printf("\nappuyer sur une touche pour quitter...");
    videBuffer();
    fgetc(stdin); // équivaut à une pause
*/

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
