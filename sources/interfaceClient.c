#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
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
//    cleanBuffer();
    return charInput() - '0';
}


/* mainMenu
 */
int mainMenu()
{
    fprintf(stdout, "\t\t\t\tWELCOME ON BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Go back\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Object list\n", MENU_CHOICE_MAIN_LIST);
    fprintf(stdout, "\t\t\t\t%d - Search object(s)\n", MENU_CHOICE_MAIN_SEARCH);
//    cleanBuffer();
    return charInput() - '0';
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

    /* Clean all the \n and \r possibly being in the login and password */
    cleanCRString(login);
    cleanCRString(password);

    return SUCESS;
}

/* displayResult
 */
int displayResult (int type, int code)
{
    /* Application codes */
    if (type == APPLICATION)
    {
        /* Application error */
        fprintf(stdout,"Application Error.\nExcuse us for the inconvenience.\n");
    }
    /* Transmission codes */
    else if (type == TRANSMISSION)
    {
        switch(code)
        {
            /* OK */
            case STATUS_CODE_OK:
                fprintf(stdout,"00 OK\n");
                break;

            /* CREATED */
            case STATUS_CODE_CREATED:
                fprintf(stdout,"01 CREATED\n");
                break;

            /* BAD REQUEST */
            case STATUS_CODE_BAD_REQUEST:
                fprintf(stdout,"-1 BAD REQUEST\n");
                fprintf(stdout,"The sent request doesn't match properly the pattern.\n");
                break;

            /* NOT CREATED */
            case STATUS_CODE_NOT_CREATED:
                fprintf(stdout,"-2 NOT CREATED\n");
                fprintf(stdout,"The account or object you are asking for doesn't seem to exist\n");
                break;

            /* INTERNAL SERVER ERROR */
            case STATUS_CODE_INTERNAL_SERVER_ERROR:
                fprintf(stdout,"-3 INTERNAL SERVER ERROR\n");
                break;

            /* CONFLICT */
            case STATUS_CODE_CONFLICT:
                fprintf(stdout,"-4 CONFLICT\n");
                break;

            /* FORBIDDEN */
            case STATUS_CODE_FORBIDDEN:
                fprintf(stdout,"-5 FORBIDDEN\n");
                break;

            /* Default case */
            default :
                fprintf(stdout,"Unknown error\n");
        }
    }
}



