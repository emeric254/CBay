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
    while ( MENU_CHOICE_QUIT != ( choixMenu = welcomeMenu() ) )
    {
        CLEAR();

        // debug
        printf("[%d]\n",choixMenu);

        switch(choixMenu)
        {
            case MENU_CHOICE_MAIN_CONNECTION:
                // pour l'instant afficher ca
                printf("\t\t\tConnection\n");

                /*
                while(MENU_CHOICE_QUIT != (choixMenu = menuConnexion()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case MENU_CHOICE_MAIN_ACCOUNT_CREATION:
                // pour l'instant afficher ca
                printf("\t\t\tAccount creation\n");

                /*
                while(MENU_CHOICE_QUIT != (choixMenu = menuCreationCompte()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case MENU_CHOICE_MAIN_ANONYMOUS:
                while(MENU_CHOICE_QUIT != (choixMenu = mainMenu()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",choixMenu);

                    switch(choixMenu)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        case MENU_CHOICE_MAIN_LIST:
                            printf("\n\t\t --- WIP >> list\n\n");
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            printf("\n\t\t --- WIP >> seach\n\n");
                            break;

                        default:
                            printf("\n\t\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                break;

            default:
                printf("\n\t\t --- Please make a correct choice !\n\n");
                break;
        }
    }

    CLEAR();
    printf("\n\t\t Thank you to use BEEP !\n\n");

/*
    printf("\npress a key to quit...\n");
    videBuffer();
    fgetc(stdin); // équivaut à une pause
*/

    return 0;
}


/*
int main() {
    char *message = NULL;

    fprintf(stdout,"mainClient !\n");

    if(!InitialisationAvecService(SERVER_ADRESS, SERVER_PORT))
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
