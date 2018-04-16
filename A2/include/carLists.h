#ifndef __CARLISTS_H__
#define __CARLISTS_H__

#include<stdio.h>

/*  runListManager
 *
 *  This function runs the bulk of the program.  It receives the users inputs, and calls
 *  other functions to perform operations based on the users input.
 *
 *  In: N/A
 *
 *  Out: N/A
 *
 *  Post: total income is printed when exiting
 *
 *  Error: N/A (See carMain.c for general errors)
 */
void runListManager();

/*  getValidOption
 *
 *  gets input from user and ensures the input is valid.  Returns the option selected by the user.
 *
 *  In: N/A
 *
 *  Out: Returns a single digit integer
 *
 *  Post: N/A
 *
 *  Error: N/A
 */
int getValidOption();

/*  addMileage
 *
 *  gets a valid mileage from the user.  Must be an integer.
 *
 *  In: N/A
 *
 *  Out: returns the mileage.
 *
 *  Post: N/A
 *
 *  Error: N/A
 */
int addMileage();

/*  addReturnDate
 *
 *  gets a valid return date from the user.  Must be of the form yymmdd
 *
 *  In: N/A
 *
 *  Out: Returns a pointer to the return date the user inputted.
 *
 *  Post: N/A
 *
 *  Error: All days are assumed to have 31 days.
 */
char * addReturnDate();

/*  calculateCost
 *
 *  calculates the cost based on the new mileage.  $40.00 flat rate and $0.15 for every kilometer after 100km.
 *
 *  In: totalIncome, oldMileage, pointer to the returned Car.
 *
 *  Out: new total income
 *
 *  Post: N/A
 *
 *  Error: N/A
 */
double calculateCost(double totalIncome, int oldMileage, Car * carSearch);

/*  loadList
 *
 *  This function loads the target file into the three lists.
 *
 *  In: filePtr (points to file), list(list to load into), toStop(keywords in file that tells function when to stop loading)
 *
 *  Out: pointer to the loaded list
 *
 *  Post: list is loaded
 *
 *  Error: file MUST be in the correct format or the program will not work
 */
Car * loadList(FILE * filePtr, Car * list, char toStop[]);

/*  saveList
 *
 *  This function saves the current lists to a file that can be reloaded the next time the program runs
 *
 *  In: filePtr, list
 *
 *  Out: N/A
 *
 *  Post:  A file is created with the saved list
 *
 *  Error:  Only works if lists in the program work.
 */
void saveList(FILE * filePtr, Car * list);

#endif
