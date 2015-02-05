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

    /*
        while(!fini) // on garde cette boucle au cas ou la requete "GET [...]" ne soit pas la premiere ligne envoyee par le client
        {
/////
            if(message != NULL)
            {
                if(extraitFichier(message, &nomFichier, &tailleNomFichier))
                {
                    if(tailleNomFichier<1)
                        retour = envoyerReponse400(); // BAD_REQUEST
                    else
                    {
                        if(!strlen(nomFichier) || !strcmp(nomFichier,"HTTP/1.1")) // pas de nom nomfichier ou '/' ?
                        {
                            free(nomFichier);
                            nomFichier=malloc(11*sizeof(char));
                            if(nomFichier!=NULL) strcpy(nomFichier,"index.html"); // on envoie la page d'accueil !
                        }

                        if(longueur_fichier(nomFichier)!=-1) // si existe
                        {
                            if(testExtension(nomFichier,".jpg"))
                                retour = envoyerReponse200JPG(nomFichier);
                            else if(testExtension(nomFichier,".ico"))
                                retour = envoyerReponse200ICO(nomFichier);
                            else if(testExtension(nomFichier,".html"))
                                retour = envoyerReponse200HTML(nomFichier);
                            else retour = envoyerReponse403(); // FORBIDDEN
                        }
                        else
                            retour = envoyerReponse404(); // NOT_FOUND
                    }

                    if(!retour)
                        envoyerReponse500(); // SERVER_INTERNAL_ERROR
                    retour = 0;
                    fini = 1;
                }
            } else  fini = 1;
        }
    */

    return ERROR_UNKNOWN;
}
