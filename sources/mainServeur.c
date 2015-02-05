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
                    // connected = TRUE;
                }
                else if(isDeleteRequest(message, length) == TRUE)
                {
                    // work with this Delete request
                }
                else if(isGetRequest(message, length) == TRUE)
                {
                    // work with this Get request
                }
                else if(isPutRequest(message, length) == TRUE)
                {
                    // work with this Put request
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
            endServer();
            return SUCESS;
        }
    }

    return ERROR_UNKNOWN;
}
