#ifndef __INTERFACECLIENT_H__
#define __INTERFACECLIENT_H__


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

/* displayResult.
 * display the result of an operation a code and a type.
 * returns nothing.
 */
int displayResult (int type, int code);

#endif
