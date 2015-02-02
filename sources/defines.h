#ifndef __DEFINE_H__
#define __DEFINE_H__

/* ... */

// Save files
#define ACC_FILE "accounts.txt"
#define OBJ_FILE "objects.txt"

//
#define TRUE 1
#define FALSE 0
#define BUFFER_LENGTH 4096
#define ERROROUTPUT stderr

//
#define SERVER_PORT "25000"
#define SERVER_ADRESS "127.0.0.1"


//
#define STATUS_LINE_LENGTH 16
#define RESPONSE_HEADER_LENGTH 64


// response header fields
#define RESPONSE_HEADER_FIELDNAME_CONTENT_LENGTH "Content-length: "
#define RESPONSE_HEADER_FIELDNAME_CONTENT_TYPE "Content-type: "


// object types
#define CONTENT_TYPE_OBJECTBID_ID 0
#define CONTENT_TYPE_USERACCOUNT_ID 0

#define CONTENT_TYPE_OBJECTBID_NAME ObjectBid
#define CONTENT_TYPE_USERACCOUNT_NAME UserAccount


//request methods
#define REQUEST_METHOD_GET "GET"
#define REQUEST_METHOD_PUT "PUT"
#define REQUEST_METHOD_CONNECT "CONNECT"
#define REQUEST_METHOD_DELETE "DELETE"


// codes retour requete positifs
#define STATUS_CODE_OK 00
#define STATUS_CODE_CREATED 01
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
#define REASON_PHRASE_INTERNAL_SERVER_ERROR "Server Error"
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


// application return codes
#define SUCESS 0
#define ERROR_OPENING -1
#define ERROR_READING -2
#define ERROR_WRITING -3
#define ERROR_READING_BUFF -4
#define ERROR_OPENING_BUFF -5
#define ERROR_WRITING_BUFF -5
#define ERROR_USER -7
#define ERROR_POINTER -8

// ObjectBid structure member length
#define OBJECTBID_NAME_LENGTH 96
#define OBJECTBID_DESCRIPTION_LENGTH 320
#define OBJECTBID_ADRESS_LENGTH 96

// UserAccount structure member length
#define USERACCOUNT_LOGIN_LENGTH 27
#define USERACCOUNT_PASSWORD_LENGTH 26
#define USERACCOUNT_NAME_LENGTH 75
#define USERACCOUNT_LASTNAME_LENGTH 64
#define USERACCOUNT_ADRESS_LENGTH 96
#define USERACCOUNT_MAIL_LENGTH 80


// menu choices
// common
#define MENU_CHOICE_QUIT 0
// welcome menu
#define MENU_CHOICE_MAIN_CONNECTION 1
#define MENU_CHOICE_MAIN_ACCOUNT_CREATION 2
#define MENU_CHOICE_MAIN_ANONYMOUS 3
// main menu
#define MENU_CHOICE_MAIN_LIST 1
#define MENU_CHOICE_MAIN_SEARCH 2



#if defined __WIN32__
    #define CLEAR() system("cls")
    #define perror(x) fprintf(ERROROUTPUT, "%d : %s\n", WSAGetLastError(), (x))
    #define close closesocket
    #define socklen_t int
#else
    #define CLEAR() system("clear")
#endif



#endif
