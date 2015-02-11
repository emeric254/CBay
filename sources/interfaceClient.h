#ifndef __INTERFACECLIENT_H__
#define __INTERFACECLIENT_H__

#include "structures.h"

/** \file interfaceClient.h
 * \brief This file provide the main function to interact with the user like
 * \displayResult, \displayObject or \mainMenu. Nearly all the user's input are
 * taken with those functions. The only exception is for the account and the
 * object creation.
 *
 */

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
 * \param list is the list to display and listSize its number of elements
 * \return nothing.
 *
 */
void displayList (ObjectBid * list, int listSize);

/** \fn int biddingInput(ObjectBid obj, int * price)
 * \brief ask the user for a price for an object
 * \param obj is the object for which we want the user to give a price
 * \return the status code of this operation
 *
 */
int biddingInput(ObjectBid obj, float * price);

/** \fn int choseObjectInList(ObjectBid * chosen, ObjectBid * list);
 * \brief display a list of object and ask to chose one to bid on
 * \param chosen is the chosen object's number to bid in the list list of
 * listSize elements
 * \return the status code of this operation
 *
 */
int choseObjectInList(int * chosen, ObjectBid * list, int listSize);

#endif
