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
    fprintf(stdout, "\t\t\t\t%d - Connection\n", MENU_CHOICE_CONNECTION);
    fprintf(stdout, "\t\t\t\t%d - Account creation\n", MENU_CHOICE_ACCOUNT_CREATION);
    fprintf(stdout, "\t\t\t\t%d - Continue anonymously\n", MENU_CHOICE_ANONYMOUS);
//    cleanBuffer();
    return getAChar() - '0';
}


/* mainMenu
 */
int mainMenu()
{
    fprintf(stdout, "\t\t\t\tWELCOME ON BEEP\n\n\n");
    fprintf(stdout, "\t\t\t\t%d - Go back\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t\t\t\t%d - Object list\n", MENU_CHOICE_MAIN_LIST);
    fprintf(stdout, "\t\t\t\t%d - Search object(s)\n", MENU_CHOICE_MAIN_SEARCH);
    fprintf(stdout, "\t\t\t\t%d - Bid for an object\n", MENU_CHOICE_MAIN_BID);
//    cleanBuffer();
    return getAChar() - '0';
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
    fgets(login,USERACCOUNT_LOGIN_LENGTH,stdin);
    fprintf(stdout,"\t\t\t\tPassword : ");
    fgets(password,USERACCOUNT_PASSWORD_LENGTH,stdin);

    /* Clean all the \n and \r possibly being in the login and password */
//    cleanCRString(login);
//    cleanCRString(password);

    return SUCCESS;
}

/* searchInput
 */
int searchInput (char* name)
{
    /* Clean the screen */
    CLEAR();

    /* Get the name */
    fprintf(stdout,"\t\t\t\tPlease enter the name of the object you're seeking\n");
    fgets(name,OBJECTBID_NAME_LENGTH,stdin);

    /* Clean all the \n and \r possibly being in the name */
//    cleanCRString(name);

    return SUCCESS;
}

/* displayResult
 */
void displayResult (int code)
{

    /* Application codes (from -10 to -99) */
    if (code < SUCCESS)
    {
        /* Application error */
        switch(code)
        {
            case ERROR_NO_LIST:
                fprintf(stdout,"No list available. Ask for one before doing this again.\n");
                break;

            default:
                fprintf(stdout,"Application Error.\nExcuse us for the inconvenience.\n");
                break;
        }
    }
    /* Transmission codes */
    else
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
                break;
        }
    }
}

/* displayObject
*/
void displayObject (ObjectBid obj)
{
	fprintf(stdout,"\t\tName : %s\n",obj.name);
	fprintf(stdout,"\t\tDescription : %s\n",obj.description);
	fprintf(stdout,"\t\tBase price : %f\n",obj.basePrice);
	fprintf(stdout,"\t\tSell start time : %ld\n",obj.startTime);
	fprintf(stdout,"\t\tSell end time : %ld\n",obj.endTime);
	fprintf(stdout,"\t\tCurrent price : %f\n\n",obj.currentBidPrice);
}

/* displayList.
*/
void displayList (ObjectBid * list, size_t listSize)
{
    int i;

    /* if the search didn't gave anything */
    if (list==NULL)
    {
        fprintf(stdout,"Sorry, no object answer to your request.\n");
    }

    /* Else print the results */
    else
    {
        for (i=0;i<(int)(listSize/sizeof(ObjectBid));i++)
        {
        	fprintf(stdout,"\t\tObject n°%d :\n",i+1);
            displayObject(list[i]);
        }
    }
}


