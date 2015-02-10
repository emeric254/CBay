#ifndef __INTERFACECLIENT_H__
#define __INTERFACECLIENT_H__

#include "structures.h"

/* welcomeMenu.
 * show welcome menu.
 * return user choice.
 */
int welcomeMenu();


/* mainMenu.
 * show main menu.
 * return user choice.
 */
int mainMenu();

/* connectionInput.
 * asks the user for a login and a password and gets their answer.
 * return a login and a password.
 */
int connectionInput (char* login, char* password);

/* searchInput.
 * asks the user for an object's name and gets their answer.
 * return an object's name.
 */
int searchInput (char* name);

/* displayResult.
 * display the result of an operation from a code.
 * returns nothing.
 */
void displayResult (int code);

/* displayObject.
 * display an object and its properties.
 * returns nothing.
 */
void displayObject (ObjectBid obj);

/* displayList.
 * display the list of available objects.
 * returns nothing.
 */
void displayList (ObjectBid * list, size_t listSize);

#endif
