#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interfaceClient.h"
#include "structures.h"


/* welcomeMenu
 */
int welcomeMenu()
{
    fprintf(stdout, " \n \t\t\
 ██████╗██████╗  █████╗ ██╗   ██╗ \n \t\t\
██╔════╝██╔══██╗██╔══██╗╚██╗ ██╔╝ \n \t\t\
██║     ██████╔╝███████║ ╚████╔╝  \n \t\t\
██║     ██╔══██╗██╔══██║  ╚██╔╝   \n \t\t\
╚██████╗██████╔╝██║  ██║   ██║    \n \t\t\
 ╚═════╝╚═════╝ ╚═╝  ╚═╝   ╚═╝    \n\n\n");
    fprintf(stdout, " %d - Quit\n", MENU_CHOICE_QUIT);
    fprintf(stdout, " %d - Connection\n", MENU_CHOICE_CONNECTION);
    fprintf(stdout, " %d - Account creation\n", MENU_CHOICE_ACCOUNT_CREATION);
    fprintf(stdout, " %d - Continue anonymously\n", MENU_CHOICE_ANONYMOUS);
//    cleanBuffer();
    return getAChar() - '0';
}


/* mainMenu
 */
int mainMenu()
{
    fprintf(stdout, " \n\
▀█████████▄     ▄████████    ▄████████    ▄███████▄ \n\
  ███    ███   ███    ███   ███    ███   ███    ███ \n\
  ███    ███   ███    █▀    ███    █▀    ███    ███ \n\
 ▄███▄▄▄██▀   ▄███▄▄▄      ▄███▄▄▄       ███    ███ \n\
▀▀███▀▀▀██▄  ▀▀███▀▀▀     ▀▀███▀▀▀     ▀█████████▀  \n\
  ███    ██▄   ███    █▄    ███    █▄    ███        \n\
  ███    ███   ███    ███   ███    ███   ███        \n\
▄█████████▀    ██████████   ██████████  ▄████▀      \n\
                                                    \n\n\n");
    fprintf(stdout, "\tWELCOME ON BEEP - 0.1a\n\n\n");
    fprintf(stdout, "\t%d - Go back\n", MENU_CHOICE_QUIT);
    fprintf(stdout, "\t%d - Object list\n", MENU_CHOICE_MAIN_LIST);
    fprintf(stdout, "\t%d - Search object(s)\n", MENU_CHOICE_MAIN_SEARCH);
    fprintf(stdout, "\t%d - Bid for an object\n", MENU_CHOICE_MAIN_BID);
//    cleanBuffer();
    return getAChar() - '0';
}

/* connectionInput
 */
int connectionInput (char* login, char* password)
{
    /* Clean the screen */
    CLEAR();
    cleanBuffer();

    /* Get the login and the password */
    fprintf(stdout,"\t\t\t\tPlease enter your login and your password\n");
    fprintf(stdout,"\t\t\t\tLogin : ");
    fgets(login,USERACCOUNT_LOGIN_LENGTH,stdin);
    if(login[strlen(login)-1]=='\n')
        login[strlen(login)-1] = '\0';
    else
        cleanBuffer();
    fprintf(stdout,"\t\t\t\tPassword : ");
    fgets(password,USERACCOUNT_PASSWORD_LENGTH,stdin);
    if(password[strlen(password)-1]=='\n')
        password[strlen(password)-1] = '\0';
    else
        cleanBuffer();

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
    if(name[strlen(name)-1]=='\n')
        name[strlen(name)-1] = '\0';
    else
        cleanBuffer();

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

            case ERROR_WRONG_TYPE:
                fprintf(stdout,"Sorry, but you don't have the rights to do that.\n");
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
                fprintf(stdout,"00 OK : your request is a success.\n");
                break;

            /* CREATED */
            case STATUS_CODE_CREATED:
                fprintf(stdout,"01 CREATED : your request is a success\n");
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
void displayList (ObjectBid * list, int listSize)
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
        for (i=0;i<listSize;i++)
        {
            fprintf(stdout,"\t\tObject n°%d :\n",i+1);
            displayObject(list[i]);
        }
    }
}

/* biddingInput
*/
int biddingInput(ObjectBid obj, float* price)
{
    /* Clean the screen */
    CLEAR();

    /* Display the object's informations */
    displayObject(obj);

    /* Get the price */
    fprintf(stdout,"Enter your price : ");
    scanf("%f",price);

    /* Check the price */
    while (*price <= obj.currentBidPrice)
    {
        fprintf(stdout,"The price you entered is incorrect.\n"
        "Please enter a price higher than the current bid : ");
        scanf("%f",price);
    }

    return SUCCESS;
}


/* choseObjectInList
*/
int choseObjectInList(int * chosen, ObjectBid * list, int listSize)
{
    /* Display the list */
    displayList(list,listSize);

    /* Get the object's number */
    fprintf(stdout,"Please chose the number of the item you want to bid on : ");
    scanf("%d",chosen);
    *chosen -= 1;

    /* Verify that the number is correct */
    while ((*chosen >= listSize) || (*chosen < 0))
    {
        fprintf(stdout,"Chose a number in the list please : ");
        scanf("%d",chosen);
        *chosen -= 1;
    }

    return SUCCESS;
}



