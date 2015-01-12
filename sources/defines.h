#ifndef __DEFINE_H__
#define __DEFINE_H__

/* ... */


//
#define TRUE 1
#define FALSE 0
#define LONGUEUR_TAMPON 4096


//
#define PORT_SERVEUR "25000"
#define ADR_SERVEUR "127.0.0.1"


// code de retours
#define ERREUR_OUVERTURE -1
#define ERREUR_LECTURE -2
#define ERREUR_ECRITURE -3
#define ERREUR_LECTURE_BUFF -4
#define ERREUR_OUVERTURE_BUFF -5
#define ERREUR_USER -6


// valeurs des choix dans les menus
#define CHOIX_MENU_QUITTER 0

#define CHOIX_MENU_ACCUEIL_CONNEXION 1
#define CHOIX_MENU_ACCUEIL_CREATIONCOMPTE 2
#define CHOIX_MENU_ACCUEIL_ANONYME 3

#define CHOIX_MENU_PRINCIPAL_LISTE 1
#define CHOIX_MENU_PRINCIPAL_RECHERCHE 2


// portabilitée
#if defined __WIN32__
    #define CLEAR() system("cls")
#else
    #define CLEAR() system("clear")
#endif


/* ... */

#endif
