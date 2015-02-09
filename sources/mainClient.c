#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int result;
    UserAccount user;
    char login[27], password[26];

    CLEAR();

    /* The Welcome Menu : Connection and Account Creation */
    while ( MENU_CHOICE_QUIT != ( menuChoice = welcomeMenu() ) )
    {
        CLEAR();

        switch(menuChoice)
        {
            case MENU_CHOICE_CONNECTION:

                /* Connect to the server */
                result=connection();

                /* The Main Menu choices : Back to the welcome menu, list
                 * the available objects or search for objects */
                while((MENU_CHOICE_QUIT != (menuChoice = mainMenu())) && (result==SUCCESS))
                {
                    CLEAR();
                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            /* nothing to do, Go Back asked */
                            break;

                        case MENU_CHOICE_MAIN_LIST:
                            /* List available objects */
                            printf("\n\t --- WIP >> list\n\n");
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            /* Searche for a particular object */
                            printf("\n\t --- WIP >> seach\n\n");
                            break;

                        default:
                            printf("\n\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }

                CLEAR();
                break;

            case MENU_CHOICE_ACCOUNT_CREATION:

                /* Create an account */
                accountCreation();

                /* Return to the welcome menu */
                CLEAR();
                break;

            case MENU_CHOICE_ANONYMOUS:

                /* The Main Menu choices : Back to the welcome menu, list
                 * the available objects or search for objects */
                while(MENU_CHOICE_QUIT != (menuChoice = mainMenu()))
                {
                    CLEAR();

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            /* nothing to do, Go Back asked */
                            break;

                        case MENU_CHOICE_MAIN_LIST:
                            /* List available objects */
                            printf("\n\t --- WIP >> list\n\n");
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            /* Searche for a particular object */
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

    /* Exit procedure */
    CLEAR();
    printf("\n\t Thank you to use BEEP !\n\n");

/*
    printf("\npress a key to quit...\n");
    cleanBuffer();
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
