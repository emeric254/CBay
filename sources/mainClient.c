#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "structures.h"
#include "interfaceClient.h"
#include "client.h"


int main(void)
{
    // vars
    int menuChoice; // user choice var
    int connected = FALSE;
    int i = 0, j = 0;

    CLEAR();

    while ( MENU_CHOICE_QUIT != ( menuChoice = welcomeMenu() ) )
    {
        CLEAR();
        
        switch(menuChoice)
        {
            case MENU_CHOICE_MAIN_CONNECTION:
                /*
                while(MENU_CHOICE_QUIT != (menuChoice = menuConnexion()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",menuChoice);
					// -----

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case MENU_CHOICE_MAIN_ACCOUNT_CREATION:
                /*
                while(MENU_CHOICE_QUIT != (menuChoice = menuCreationCompte()))
                {
                    CLEAR();

                    // debug
                    printf("[%d]\n",menuChoice);

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        default:
                            printf("\n\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                */
                break;

            case MENU_CHOICE_MAIN_ANONYMOUS:
                while(MENU_CHOICE_QUIT != (menuChoice = mainMenu()))
                {
                    CLEAR();

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        case MENU_CHOICE_MAIN_LIST:
                            printf("\n\t --- WIP >> list\n\n");
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            printf("\n\t --- WIP >> seach\n\n");
                            break;

                        default:
                            printf("\n\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                break;

            default:
                printf("\n\t --- Please make a correct choice !\n\n");
                break;
        }
    }

    CLEAR();
    printf("\n\t Thank you to use BEEP !\n\n");

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
