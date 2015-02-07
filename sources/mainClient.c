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
    int statusCode;
    UserAccount user;
    char *response=NULL;
    char login[27], password[26];

    CLEAR();

    while ( MENU_CHOICE_QUIT != ( menuChoice = welcomeMenu() ) )
    {
        CLEAR();
        
        switch(menuChoice)
        {
            case MENU_CHOICE_CONNECTION:
            	/* Ask for a login and a password */
            	connectionInput(login,password);
            	
            	/* Send a connection request to the server */
            	sendConnect(login,password);
            	
            	/* Get the answer */
            	response=receiveBinary();
            	
            	/* Extract the status code and the reason phrase from the answer */
            	
            	
            	/* Treat the answer : either OK or NOT_CREATED */
            	if (statusCode == STATUS_CODE_OK)
            	{
            		/* Connection granted */
            		
            	}
            	else if (statusCode == STATUS_CODE_NOT_CREATED)
            	{
            		/* Connection denied */
            	}
            	else
            	{
            		/* Error */
            	}
            	
                CLEAR();
                break;
                /* After connection => to the main menu */

            case MENU_CHOICE_ACCOUNT_CREATION:
            	/* Create an account */
            	userInput();
            	
            	while (statusCode == STATUS_CODE_NOT_CREATED && i < 3)
            	{
		        	/* Send the new account to the server */
		        	sendPut(); /* Need to be written */
		        	
		        	/* Get the answer */
		        	response=ReceiveBinary();
		        	
		        	/* Extract the status code and the reason phrase from the answer */
		        	
		        	
		        	/* If the answer is not CREATED, resend it */
		        }
		    		
        		/* After 3 fail send, stop and display an error (type to define) */
        		if (statusCode == STATUS_CODE_NOT_CREATED && i == 3)
        		{
        			/* Error */
        		}
            	
				CLEAR();
                break;
                /* After the account creation => to the welcome menu */

            case MENU_CHOICE_ANONYMOUS:
                while(MENU_CHOICE_QUIT != (menuChoice = mainMenu()))
                {
                    CLEAR();

                    switch(menuChoice)
                    {
                        case MENU_CHOICE_QUIT:
                            // rien à faire car retour demandé
                            break;

                        case MENU_CHOICE_MAIN_LIST:
                        	// List available objects
                            printf("\n\t --- WIP >> list\n\n");
                            break;

                        case MENU_CHOICE_MAIN_SEARCH:
                        	// Searche for a particular object
                            printf("\n\t --- WIP >> seach\n\n");
                            break;

                        default:
                            printf("\n\t --- Please make a correct choice !\n\n");
                            break;
                    }
                }
                CLEAR();
                break;
                /* To the main menu */

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
    videBuffer();
    fgetc(stdin); // équivaut à une pause
*/

    return 0;
}

/*while(MENU_CHOICE_QUIT != (menuChoice = mainMenu()))
{
    CLEAR();

    switch(menuChoice)
    {
        case MENU_CHOICE_QUIT:
            // rien à faire car retour demandé
            break;

        case MENU_CHOICE_MAIN_LIST:
        	// List available objects
            printf("\n\t --- WIP >> list\n\n");
            break;

        case MENU_CHOICE_MAIN_SEARCH:
        	// Searche for a particular object
            printf("\n\t --- WIP >> seach\n\n");
            break;

        default:
            printf("\n\t --- Please make a correct choice !\n\n");
            break;
    }
}
CLEAR();*/

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
