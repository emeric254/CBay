#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "defines.h"
#include "structures.h"
#include "serveur.h"

int main()
{
    char *message = NULL;
    int length = 0;

    int end = FALSE;
    int quit = FALSE;
    int connected = FALSE;

    int state = SUCESS;

    char * ptrLogin = NULL;
    int sizeLogin = 0;
    char * ptrPassword = NULL;
    int sizePasword = 0;

    char accountType = ACCOUNT_TYPE_UNKNOW;

    char login[USERACCOUNT_LOGIN_LENGTH];
    char password[USERACCOUNT_PASSWORD_LENGTH];

    ObjectBid * objects = NULL;
    int nbrObjects = 0;
    ObjectBid * ptrObject = NULL;

    UserAccount * accounts = NULL;
    int nbrAccount = 0;
    UserAccount * ptrAccount = NULL;

    if((state = allObjLoad(&objects, &nbrObjects)) != SUCESS)
        return state;

    if((state = allAccLoad(&accounts, &nbrAccount)) != SUCESS)
        return state;

    Init(SERVER_PORT);

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

                    // work with this Connect request
                    if((state = splitConnectRequest(message, length, ptrLogin, ptrPassword, &sizeLogin, &sizePasword)) != SUCESS)
                        return state;
                    strncpy(login,ptrLogin,sizeLogin);
                    strncpy(password,ptrPassword,sizePasword);
                    // if pseudo && login in one of account >> then connected = TRUE;
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
                    if(connected == TRUE && accountType == ACCOUNT_TYPE_ADMIN)
                    {
                        // work with this Get account request
                    }
                    else
                    {
                        // work with this Get object request
                    }
                }
                else if(isPutRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Put request
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
                    // end = TRUE; // end communication with the client, 'cause it's a bad guy
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
                        end = TRUE;
                        break;
                    default:
                        fprintf(ERROROUTPUT, "%s >> %d >> %d\n", ERROR_OUTPUT_LABEL, ERROR_UNKNOWN, length);
                        end = TRUE;
                        quit = TRUE;
                        break;
                }
            }

            // clean memory
            free(message);
            // safety !
            message = NULL;
        }

        endClient();

        if (quit == TRUE)
        {
            free(objects);
            free(accounts);
            endServer();
            return SUCESS;
        }
    }

    return ERROR_UNKNOWN;
}
