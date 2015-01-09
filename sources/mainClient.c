#include <stdio.h>
#include <stdlib.h>
#include "defines.h"
#include "client.h"

#define PORT_SERVEUR "80"
#define ADR_SERVEUR "www.stri.ups-tlse.fr"

int main() {
    char *message = NULL;

    fprintf(stdout,"mainClient !\n");

    if(!InitialisationAvecService(ADR_SERVEUR, PORT_SERVEUR))
    {
        fprintf(stderr,"Erreur d'initialisation !");
        return 1;
    }

    if(Emission("GET / HTTP/1.0\n\n")){
        while (message = Reception()){
            fprintf(stdout,"%s",message);
            free(message);
        }
    }

    Terminaison();

    return 0;
}
