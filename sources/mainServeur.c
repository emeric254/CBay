#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "serveur.h"

int main() {
	char *message = NULL;
	char *nomFichier = NULL;
	size_t tailleNomFichier=0;
	int retour = 0;
	int fini = 0;

	Initialisation();

	while(1)
	{
		AttenteClient();
		fini = 0;

		while(!fini) // on garde cette boucle au cas ou la requete "GET [...]" ne soit pas la premiere ligne envoyee par le client
		{
			message = Reception();
			
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
			} else	fini = 1;

			// nettoyage
			free(message);
			message = NULL;
			free(nomFichier);
			nomFichier = NULL;
		}
		TerminaisonClient();
	}

	return 0;
}
