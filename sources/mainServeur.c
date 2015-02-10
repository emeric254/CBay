#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "structures.h"
#include "serveur.h"

int main()
{
    char *message = NULL; // message received from a client
    int length = 0; // its length

    int end = FALSE; // server end
    int quit = FALSE; // want to end client connection
    int connected = FALSE; // client connection state

    int state = SUCCESS; // represents return statement

    char * ptrLogin = NULL; //
    int sizeLogin = 0; // its length
    char * ptrPassword = NULL; //
    int sizePasword = 0; // its length

    char accountType = ACCOUNT_TYPE_UNKNOW; // client account type

    char login[USERACCOUNT_LOGIN_LENGTH]; // client login
    char password[USERACCOUNT_PASSWORD_LENGTH]; // client password
    long int id = -1; // client's id

    ObjectBid * objects = NULL; // table of objects
    int nbrObjects = 0; // number of objects
    ObjectBid * ptrObject = NULL; // ptr to an object

    UserAccount * accounts = NULL; // table of accounts
    int nbrAccount = 0; // number of accounts
    UserAccount * ptrAccount = NULL; // ptr to an account

    ConfidentialIDS * ids = NULL; // table of IDS
    int nbrIDS = 0; // number of IDS

    // table of objects loading
    if((state = allObjLoad(&objects, &nbrObjects)) != SUCCESS)
        return state;

    // table of accounts loading
    if((state = allAccLoad(&accounts, &nbrAccount)) != SUCCESS)
        return state;

    // init server
    Init(SERVER_PORT);

    // working cycle
    while(1)
    {
        connectWait();
        end = FALSE;

        while (end == FALSE)
        {
            length = receiveBinary(message);
            if (length > 0)
            {
                printf("%s\n",message);
                if(isConnectRequest(message, length) == TRUE)
                {
                    if(connected != TRUE) // not already connected
                    {
                        if((state = splitConnectRequest(message, length, ptrLogin, ptrPassword, &sizeLogin, &sizePasword)) != SUCCESS)
                            return state;
                        strncpy(login,ptrLogin,sizeLogin);
                        strncpy(password,ptrPassword,sizePasword);
                        // if pseudo && login in one of account >> then connected = TRUE;
                        if ( idsInTable(login, password, ids, nbrIDS, &id) == TRUE )
                        {
                            // he sucess in connection
                            sendStatusLine(STATUS_CODE_OK);
                        }
                        else
                        {
                            // wrong ids
                            sendStatusLine(STATUS_CODE_FORBIDDEN);
                        }
                    }
                    // else { /* already connected ! */}
                }
                else if(isDeleteRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Delete request
                    }
                    else
                    {
                        fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                        sendStatusLine(STATUS_CODE_FORBIDDEN);
                    }
                }
                else if(isGetRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Get request as ?
                        // test type of data
                        // is inTables ?
                        /*
                        if (accountType == ACCOUNT_TYPE_ADMIN)
                        else if (accountType == ACCOUNT_TYPE_VENDOR)
                        else if (accountType == ACCOUNT_TYPE_USER)
                        else // server fail !
                        */
                    }
                    else
                    {
                        // work with this Get request as anonymous
                        // test type of data
                        // is inTables ?
                    }
                }
                else if(isPutRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Put request
                        // test type of data
                        // is new or alredy inTables ?
                        // so creation or update
                    }
                    else
                    {
                        fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                        sendStatusLine(STATUS_CODE_FORBIDDEN);
                    }
                }
                else
                {
                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                    sendStatusLine(STATUS_CODE_BAD_REQUEST);
                    // end = TRUE; // end communication with the client, 'cause it's a bad guy : he send wrong request
                }
            }
            else
            {
                switch(length)
                {
                    case ERROR_EMPTY_BUFF: // == 0
                        // just nothing received ...
                        // so continue to communicate with the client
                        break;
                    case ERROR_RECEIVING:
                        fprintf(ERROROUTPUT, "%s >> %d\n", ERROR_OUTPUT_LABEL, ERROR_RECEIVING);
                        end = TRUE; // end client connection
                        break;
                    default:
                        fprintf(ERROROUTPUT, "%s >> %d >> %d\n", ERROR_OUTPUT_LABEL, ERROR_UNKNOWN, length);
                        end = TRUE; // end client connection
                        quit = TRUE; // and quit the server
                        break;
                }
            }

            // clean memory
            free(message);
            // safety !
            message = NULL;
        }

        // end client connection properly
        endClient();

        // server will quit
        if (quit == TRUE)
        {
            free(objects);
            free(accounts);
            endServer();
            return SUCCESS;
        }
    }

    // it's impossible breaking the working cycle to go here
    return ERROR_UNKNOWN;
}
