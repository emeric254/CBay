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


// codes retour requete positifs
#define STATUS_CODE_OK 0
#define STATUS_CODE_CREATED 1
//reason phrases
#define REASON_PHRASE_OK 0
#define REASON_PHRASE_CREATED 1


// codes retour requete negatifs
#define STATUS_CODE_BAD_REQUEST -1
#define STATUS_CODE_NOT_CREATED -2
#define STATUS_CODE_INTERNAL_SERVER_ERROR -3
#define STATUS_CODE_CONFLICT -4
#define STATUS_CODE_FORBIDDEN -5
// reason phrases
#define REASON_PHRASE_BAD_REQUEST -1
#define REASON_PHRASE_NOT_CREATED -2
#define REASON_PHRASE_INTERNAL_SERVER_ERROR -3
#define REASON_PHRASE_CONFLICT -4
#define REASON_PHRASE_FORBIDDEN -5



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



#endif


/*

6.1.2 Status-line length

   The CHAR length of the status-line is described below :
   |---------------|----|-----------------|----|
   | {Status Code} | SP | {Reason Phrase} | CR |
   |---------------|----|-----------------|----|
   |       2       |  1 |        12       |  1 |
   |---------------|----|-----------------|----|

   (total CHAR length) = 16

   6.2   Response Header Fields

   The CHAR length of the response header line is described below :
   |----------------|---|----|------------------|---|-»
   | Content-length | : | SP | {Content-length} | ; |-»
   |----------------|---|----|------------------|---|-»
   |       14       | 1 |  1 |        15        | 1 |-»
   |----------------|---|----|------------------|---|-»

   «-|--------------|---|----|----------------|---|----|
   «-| Content-type | : | SP | {Content-type} | ; | CR |
   «-|--------------|---|----|----------------|---|----|
   «-|      12      | 1 |  1 |       16       | 1 |  1 |
   «-|--------------|---|----|----------------|---|----|

   (total CHAR length) = 64

*/


/*
 
 9.1   GET
  
   The GET method enable the client to ask the server to send back an entity.
   This method requires X parameters and have the following length :
   |-----|----|----------|---|----|
   | GET | SP | {OBJECT} | ; | CR |
   |-----|----|----------|---|----|
   |  3  |  1 | {OBJECT} | 1 |  1 |
   |-----|----|----------|---|----|

   (total CHAR length) = 6
   + ({Object} length)

   9.2   PUT
   
   The client requests the server to store the a requested entity sent
   in the core of the request.
   This method requires X parameters and have the following length :
   |-----|----|----------|---|----|
   | PUT | SP | {OBJECT} | ; | CR |
   |-----|----|----------|---|----|
   |  3  |  1 | {OBJECT} | 1 |  1 |
   |-----|----|----------|---|----|

   (total CHAR length) = 6
   + ({Object} length)

   9.3   DELETE
   
   The client requests the server to delete the requested entity from
   his database. For the entity types, cf section 7. To delete an
   object or a user account, the client must be authenticed as the
   object's creator or an administrator.
   This method requires one parameters and have the following length :
   |--------|----|----------|---|----|
   | DELETE | SP | {OBJECT} | ; | CR |
   |--------|----|----------|---|----|
   |    6   |  1 | {OBJECT} | 1 |  1 |
   |--------|----|----------|---|----|

   (total CHAR length) = 9
   + ({Object} length)

   9.4   CONNECT
   
   The CONNECT method is used by the client to establish a permanent
   connection with the server.
   This method requires two parameters and have the following length :
   |---------|----|---------|---|------------|---|----|
   | CONNECT | SP | {LOGIN} | ; | {PASSWORD} | ; | CR |
   |---------|----|---------|---|------------|---|----|
   |    7    |  1 |    27   | 1 |     26     | 1 |  1 |
   |---------|----|---------|---|------------|---|----|

   (total CHAR length) = 64
  
*/


