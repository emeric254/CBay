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


//
#define STATUS_LINE_LENGTH 16
#define RESPONSE_HEADER_LENGTH 64


// response header fields
#define RESPONSE_HEADER_FIELDNAME_CONTENT_LENGTH "Content-length"
#define RESPONSE_HEADER_FIELDNAME_CONTENT_TYPE "Content-type"


//request methods
#define REQUEST_METHOD_GET "GET"
#define REQUEST_METHOD_PUT "PUT"
#define REQUEST_METHOD_CONNECT "CONNECT"
#define REQUEST_METHOD_DELETE "DELETE"


// codes retour requete positifs
#define STATUS_CODE_OK 0
#define STATUS_CODE_CREATED 1
//reason phrases
#define REASON_PHRASE_OK "Ok"
#define REASON_PHRASE_CREATED "Created"


// codes retour requete negatifs
#define STATUS_CODE_BAD_REQUEST -1
#define STATUS_CODE_NOT_CREATED -2
#define STATUS_CODE_INTERNAL_SERVER_ERROR -3
#define STATUS_CODE_CONFLICT -4
#define STATUS_CODE_FORBIDDEN -5
// reason phrases
#define REASON_PHRASE_BAD_REQUEST "Bad Request"
#define REASON_PHRASE_NOT_CREATED "Not Created"
#define REASON_PHRASE_INTERNAL_SERVER_ERROR "Internal Server Error"
#define REASON_PHRASE_CONFLICT "Conflict"
#define REASON_PHRASE_FORBIDDEN "Forbidden"

// account types
#define ACCOUNT_TYPE_ADMIN 'a'
#define ACCOUNT_TYPE_VENDOR 'v'
#define ACCOUNT_TYPE_USER 'u'
// account labels
#define ACCOUNT_LABEL_ADMIN "Admin, become a god ;) "
#define ACCOUNT_LABEL_VENDOR "Vendor, limited to sell things"
#define ACCOUNT_LABEL_USER "User, limited to bought things"


// code de retours application
#define ERREUR_OUVERTURE -1
#define ERREUR_LECTURE -2
#define ERREUR_ECRITURE -3
#define ERREUR_LECTURE_BUFF -4
#define ERREUR_OUVERTURE_BUFF -5
#define ERREUR_USER -6
#define ERREUR_POINTEUR -6


// valeurs des choix dans les menus
// commun
#define CHOIX_MENU_QUITTER 0
// menu accueil
#define CHOIX_MENU_ACCUEIL_CONNEXION 1
#define CHOIX_MENU_ACCUEIL_CREATIONCOMPTE 2
#define CHOIX_MENU_ACCUEIL_ANONYME 3
// menu principal
#define CHOIX_MENU_PRINCIPAL_LISTE 1
#define CHOIX_MENU_PRINCIPAL_RECHERCHE 2



// portabilitée
#if defined __WIN32__
    #define CLEAR() system("cls")
#else
    #define CLEAR() system("clear")
#endif



#endif
