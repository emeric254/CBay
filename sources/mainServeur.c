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
        if(state != ERROR_OPENING)
            return state;

    // table of accounts loading
    if((state = allAccLoad(&accounts, &nbrAccount)) != SUCCESS)
        if(state != ERROR_OPENING)
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
            length = receiveBinary(&message);

//            printf("message >>%d>>%s\n",length,message);

            if (length > 0 && message != NULL)
            {

                if(isConnectRequest(message, length) == TRUE) //        CONNECT ------------------------------------------------------------------------
                {
                    if(connected != TRUE) // not already connected
                    {
                        if((state = splitConnectRequest(message, length, ptrLogin, ptrPassword, &sizeLogin, &sizePasword)) != SUCCESS)
                        {
                            fprintf(ERROROUTPUT,">>> %d", state);
                            fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                            sendStatusLine(STATUS_CODE_BAD_REQUEST);
                        }

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
                else if(isDeleteRequest(message, length) == TRUE) //    DELETE ------------------------------------------------------------------------
                {
                    if(connected == TRUE)
                    {
                        // work with this Delete request
                        if ((state = splitDeleteRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                        {
                            fprintf(ERROROUTPUT,">>> %d", state);
                            fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                            sendStatusLine(STATUS_CODE_BAD_REQUEST);
                        }

                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || id == ptrAccount->IDS.id)
                                {
                                    // admin || user can delete his account
                                    removeUserAccountInTable(&accounts, &nbrAccount, ptrAccount);
                                    // save this new account table
                                    allAccSave(accounts, nbrAccount);
                                    // disconnect the user who delete his own account
                                    if(id == ptrAccount->IDS.id)
                                        end = TRUE;
                                    // ok
                                    sendStatusLine(STATUS_CODE_OK);
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
                                if(accountType == ACCOUNT_TYPE_ADMIN || (accountType == ACCOUNT_TYPE_VENDOR && ptrObject->idVendor == id))
                                {
                                    // admin || vendor of this object
                                    removeObjectBidInTable(&objects, &nbrObjects, ptrObject);
                                    // save the new table
                                    allObjSave(objects, nbrObjects);
                                    // ok
                                    sendStatusLine(STATUS_CODE_OK);
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
                else if(isGetRequest(message, length) == TRUE) //       GET ------------------------------------------------------------------------
                {
                    if(connected == TRUE)
                    {
                        // work with this Get request
                        if ((state = splitPutRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                        {
                            fprintf(ERROROUTPUT,">>> %d", state);
                            fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                            sendStatusLine(STATUS_CODE_BAD_REQUEST);
                        }

                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                // admin || user can show his account
                                if(accountType != ACCOUNT_TYPE_ADMIN && id != ptrAccount->IDS.id)
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                                else
                                    if((state = answerUserAccount(ptrAccount)) != SUCCESS)
                                        fprintf(ERROROUTPUT,">>> %d\n", state);
                            }
                            else // user doesn't have his UserAccount
                            {
                                // try to send user's UserAccount
                                UserAccount temp;
                                temp.IDS.id = id;

                                if(userInTable(&temp, accounts, nbrAccount, ptrAccount) == TRUE)
                                {
                                    if((state = answerUserAccount(ptrAccount)) != SUCCESS)
                                        fprintf(ERROROUTPUT,">>> %d\n", state);
                                }
                                else // unknown account, non exsitant account
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                    sendStatusLine(STATUS_CODE_BAD_REQUEST);
                                }
                            }
                        }
                        else if(isObjectBid(sizeData) == TRUE)
                        {
                            if(objInTable((ObjectBid*)ptrData, objects, nbrObjects, ptrObject) == TRUE)
                            {
                                if((state = answerObjectBid(ptrObject)) != SUCCESS)
                                    fprintf(ERROROUTPUT,">>> %d\n", state);
                            }
                            else if (searchObjectBidInTable(objects, nbrObjects, (ObjectBid*)ptrData, ptrObject) == TRUE) // search by name
                            {
                                if((state = answerObjectBid(ptrObject)) != SUCCESS)
                                    fprintf(ERROROUTPUT,">>> %d\n", state);
                            }
                            else
                            {
                                 // non existant
                                fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_BAD_REQUEST, REASON_PHRASE_BAD_REQUEST, message);
                                sendStatusLine(STATUS_CODE_BAD_REQUEST);
                            }
                        }
                        else if(sizeData == 0)
                        {
                            if((state = answerObjectBidTable(objects, nbrObjects)) != SUCCESS)
                                fprintf(ERROROUTPUT,">>> %d\n", state);
                        }
                    }
                    else // not connected
                    {
                        fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                        sendStatusLine(STATUS_CODE_FORBIDDEN);
                    }
                }
                else if(isPutRequest(message, length) == TRUE) //       PUT ------------------------------------------------------------------------
                {
                    // work with this Put request
                    if ((state = splitPutRequest(message, length, ptrData, &sizeData)) != SUCCESS)
                        return state;

                    if(connected == TRUE)
                    {
                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                if(accountType == ACCOUNT_TYPE_ADMIN || id == ptrAccount->IDS.id)
                                {
                                    // admin || user can update his account

                                    //@TODO update this account

                                    allAccSave(accounts, nbrAccount);
                                    sendStatusLine(STATUS_CODE_OK);
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
                                if(accountType == ACCOUNT_TYPE_ADMIN || (accountType == ACCOUNT_TYPE_VENDOR && id == ptrObject->idVendor))
                                {
                                    // admin || vendor of this object

                                    //@TODO update this object

                                    allObjSave(objects, nbrObjects);
                                    sendStatusLine(STATUS_CODE_OK);
                                }
                                else
                                {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                                }
                            }
                            else
                            {
                                // add the new object
                                int idmax = 0;

                                //@TODO get the max id used in ObjectBid table

                                ((ObjectBid*)ptrData)->id = idmax+1;
                                addObjectBidInTable(&objects, &nbrObjects, (ObjectBid*) ptrData);
                                sendStatusLine(STATUS_CODE_CREATED);
                            }
                        }
                    }
                    else // not connected
                    {
                        if(isAccountUser(sizeData) == TRUE)
                        {
                            if(userInTable((UserAccount*)ptrData, accounts, nbrAccount, ptrAccount) == TRUE)
                            {
                                    fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                                    sendStatusLine(STATUS_CODE_FORBIDDEN);
                            }
                            else
                            {
                                // add the new user
                                int idmax = 0;

                                //@TODO get the max id used in UserAccount table

                                ((UserAccount*)ptrData)->IDS.id = idmax+1;
                                addUserAccountInTable(&accounts, &nbrAccount, (UserAccount*)ptrData, &ids, &nbrIDS);
                                sendStatusLine(STATUS_CODE_CREATED);
                            }
                        }
                        else
                        {
                            fprintf(ERROROUTPUT,"%d >> %s >> %s\n", STATUS_CODE_FORBIDDEN, REASON_PHRASE_FORBIDDEN, message);
                            sendStatusLine(STATUS_CODE_FORBIDDEN);
                        }
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
                        fprintf(ERROROUTPUT, "%s >> %d >> %d >> %s\n", ERROR_OUTPUT_LABEL, ERROR_UNKNOWN, length, message);
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
