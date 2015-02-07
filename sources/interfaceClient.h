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

/* ... */

#endif
