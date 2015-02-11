#ifndef __INTERFACECLIENT_H__
#define __INTERFACECLIENT_H__

#include "structures.h"

/** \fn int welcomeMenu()
 * \brief show welcome menu.
 * \return user choice.
 *
 */
int welcomeMenu();


/** \fn int mainMenu()
 * \brief show main menu.
 * \return user choice.
 *
 */
int mainMenu();

/** \fn int connectionInput(char* login, char* password)
 * \brief asks the user for a login and a password and gets their answer.
 * \param login and password are the information needed to connect to the CBay
 * service
 * \return the status code of this operation
 *
 */
int connectionInput (char* login, char* password);

/** \fn int searchInput(char* name)
 * \brief asks the user for an object's name and gets their answer.
 * \param name is the name of an object the user will enter.
 * \return the status code of this operation
 *
 */
int searchInput (char* name);

/** \fn void displayResult(int code)
 * \brief display the result of an operation from a code.
 * \param code is the status or application code which will determine the
 * message displayed
 * \return nothing.
 *
 */
void displayResult (int code);

/** \fn void displayObject(ObjectBid obj)
 * \brief display an object and its properties.
 * \param obj is the object to display
 * \return nothing.
 *
 */
void displayObject (ObjectBid obj);

/** \fn void displayList(ObjectBid * list, size_t listSize)
 * \brief display the list of available objects.
 * \param list is the list to display and listSize its size in bytes
 * \return nothing.
 *
 */
void displayList (ObjectBid * list, size_t listSize);

/** \fn int biddingInput(ObjectBid obj, int * price)
 * \brief ask the user for a price for an object
 * \param obj is the object for which we want the user to give a price
 * \return the status code of this operation
 *
 */
int biddingInput(ObjectBid obj, float * price);

#endif
