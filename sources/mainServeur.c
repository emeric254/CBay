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

    Init(SERVER_PORT);

    while(1)
    {
        connectWait();
        end = FALSE;

        while (end == FALSE)
        {
            length = receiveBinary(message);
            if (length > 0)
                printf("%s\n",message);
                //@TODO work with the mesage !!
                // is it a valid request ?
                // or not ? >> ERROR_READING_BUFF
            else
                switch(length)
                {
                    case ERROR_RECEIVING:
                        fprintf(ERROROUTPUT, "%s >> %d\n", ERROR_OUTPUT_LABEL, ERROR_RECEIVING);
                        break;
                    case ERROR_EMPTY_BUFF:
                        // just nothing received ...
                        break;
                    default:
                        fprintf(ERROROUTPUT, "%s >> %d\n", ERROR_OUTPUT_LABEL, ERROR_UNKNOWN);
                        break;
                }
        }

        endClient();

        //@TODO if (quit)
        //{
            //endServer();
            //return SUCESS;
        //}
    }

    /*

    char *nomFichier = NULL;
    size_t tailleNomFichier=0;
    int retour = 0;

    while(1)
    {
//////
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

            // nettoyage
            free(message);
            message = NULL;
            free(nomFichier);
            nomFichier = NULL;
        }
    }
    */

    return ERROR_UNKNOWN;
}
