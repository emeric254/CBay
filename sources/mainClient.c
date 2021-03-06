#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"
#include "interfaceClient.h"
#include "client.h"


int main(void)
{
    // vars
    int menuChoice; // user choice var
    int result;
    int listSize=0;
    ObjectBid* list=NULL;
    UserAccount user;

    CLEAR();

    Init(SERVER_ADRESS);

    /* The Welcome Menu : Connection and Account Creation */
    while ( MENU_CHOICE_QUIT != ( menuChoice = welcomeMenu() ) )
    {
        CLEAR();

        switch(menuChoice)
        {
            case MENU_CHOICE_CONNECTION:

                /* Connect to the server */
                result=connection(&user);

                /* The Main Menu choices : go back to the welcome menu, list
                 * the available objects or search for objects */
                while((result==SUCCESS) && (MENU_CHOICE_QUIT != (menuChoice = mainMenu())))
                {
                    CLEAR();

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            /* nothing to do, Go Back asked */
                            break;

                        case MENU_CHOICE_MAIN_LIST:

                            /* List available objects */
                            listObjects(&list,&listSize);
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            /* Search for a particular object */
                            searchObject(list,listSize);
                            break;

                        case MENU_CHOICE_MAIN_BID:
                            /* Make a bid on an object */
                            bidObject(user,&list,listSize);
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
                            listObjects(&list,&listSize);
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                            /* Search for a particular object */
                            searchObject(list,listSize);
                            break;

                        case MENU_CHOICE_MAIN_BID:
                            /* Make a bid on an object */
                            fprintf(stdout,"You need an account in order to bid.\n");
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


