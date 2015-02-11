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


    char * ptrTemp = NULL; // temporary ptr to data
    char * ptrData = NULL; // ptr to data
    int sizeData = 0; // size of data


    ObjectBid * objects = NULL; // table of objects
    int nbrObjects = 0; // number of objects
    ObjectBid * ptrObject = NULL; // current parsed object

    UserAccount * accounts = NULL; // table of accounts
    int nbrAccount = 0; // number of accounts
    UserAccount * ptrAccount = NULL; // current parsed account

    ConfidentialIDS * ids = NULL; // table of IDS
    int nbrIDS = 0; // number of IDS
    ConfidentialIDS * ptrIDS = NULL; // current parsed IDS


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
                        if ( idsInTable(login, password, ids, nbrIDS, ptrIDS) == TRUE )
                        {
                            // he sucess in connection
                            sendStatusLine(STATUS_CODE_OK);
                            connected = TRUE;
                        }
                        else
                        {
                            // wrong ids
                            fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
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
                        if ((state = splitDeleteRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                            return state;

                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || id == ptrAccount->id)
                                {
                                    // admin || user can delete his account
                                    //@TODO delete this account
                                    if(id == ptrAccount->id)
                                        end = TRUE;
                                    // save this new account table
                                }
                                else
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                            }
                            else // non existant
                            {
                                fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                sendStatusLine(STATUS_CODE_BAD_REQUEST);
                            }
                        }
                        else if(isObjectBid(sizeData) == TRUE)
                        {
                            if(objInTable((ObjectBid*)ptrData, objects, nbrObjects, ptrObject) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || (accountType == ACCOUNT_LABEL_VENDOR && ptrObject->idVendor == id))
                                {
                                    // admin || vendor of this object
                                    //@TODO delete this object
                                    // save this new object table
                                }
                                else
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                            }
                            else // non existant
                            {
                                fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                sendStatusLine(STATUS_CODE_BAD_REQUEST);
                            }
                        }
                    }
                    else // not connected
                    {
                        fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                        sendStatusLine(STATUS_CODE_FORBIDDEN);
                    }
                }
                else if(isGetRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Get request
                        if ((state = splitPutRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                            return state;
                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                // admin || user can update his account
                            }
                            else // non existant
                            {
                                fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                sendStatusLine(STATUS_CODE_BAD_REQUEST);
                            }
                        }
                        else if(isObjectBid(sizeData) == TRUE)
                        {
                            if(objInTable((ObjectBid*)ptrData, objects, nbrObjects, ptrObject) == TRUE)
                            {

                            }
                            else if (FALSE) // search by name
                            {
                                // return result
                            }
                            else
                            {
                                 // non existant
                                fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                sendStatusLine(STATUS_CODE_BAD_REQUEST);
                            }
                        }
                    }
                    else // not connected
                    {
                        fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                        sendStatusLine(STATUS_CODE_FORBIDDEN);
                    }
                }
                else if(isPutRequest(message, length) == TRUE)
                {
                    if(connected == TRUE)
                    {
                        // work with this Put request
                        if ((state = splitPutRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                            return state;
                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || id == ptrAccount->id)
                                {
                                    // admin || user can update his account
                                    //@TODO update this account
                                    allAccSave(accounts, nbrAccount);
                                }
                                else
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                            }
                        }
                        else if(isObjectBid(sizeData) == TRUE)
                        {
                            if(objInTable((ObjectBid*)ptrData, objects, nbrObjects, ptrObject) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || (accountType == ACCOUNT_LABEL_VENDOR && ptrObject->idVendor == id))
                                {
                                    // admin || vendor of this object
                                    //@TODO update this object
                                    allObjSave(objects, nbrObjects);
                                }
                                else
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                            }
                        }
                    }
                    else // not connected
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

        // erase saved data
        strcpy(login,"");
        strcpy(password,"");

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
