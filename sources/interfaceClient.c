#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
#include "defines.h"
#include "structures.h"


/* welcomeMenu
 */
int welcomeMenu()
{
    fprintf(stdout, "\t\t\t\tWELCOME ON BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Quit\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Connection\n", MENU_CHOICE_MAIN_CONNECTION);
    fprintf(stdout, "\t\t\t\t%d - Account creation\n", MENU_CHOICE_MAIN_ACCOUNT_CREATION);
    fprintf(stdout, "\t\t\t\t%d - Continue anonymously\n", MENU_CHOICE_MAIN_ANONYMOUS);
//    videBuffer();
    return saisieChar() - '0';
}


/* mainMenu
 */
int mainMenu()
{
    fprintf(stdout, "\t\t\t\tWELCOME ON BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Go back\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Object list\n", MENU_CHOICE_MAIN_LIST);
    fprintf(stdout, "\t\t\t\t%d - Search object(s)\n", MENU_CHOICE_MAIN_SEARCH);
//    videBuffer();
    return saisieChar() - '0';
}

/* connectionInput
 */
int connectionInput (char* login, char* password)
{
	/* Clean the screen */
	CLEAR();
	
	/* Get the login and the password */
	fprintf(stdout,"\t\t\t\tPlease enter your login and your password\n");
	fprintf(stdout,"\t\t\t\tLogin : ");
	fgets(login,27,stdin);	
	fprintf(stdout,"\t\t\t\tPassword : ");
	fgets(password,26,stdin);
	
	/* Clean all the \n and EOF possibly being in the login and password strings */
	cleanCRString(login);
	cleanCRString(password);
	
	return SUCESS;
}


