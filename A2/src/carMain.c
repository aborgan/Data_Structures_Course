/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 *
 *  This program creates three linked lists: available-for-rent, rented, and inRepair.  The user
 *  may add cars to the available for rent list, return a rented car (a fee is charged depending on how far
 *  the car was driven while rented), shift the car from repair to availble for rent list, rent the next
 *  available car, and print out all lists.  All lists are sorted from lowest mileage to highest mileage.
 *   When a car is rented, the car with the lowest mileage is always rented.
 *
 *  In: N/A
 *
 *  Out: N/A
 *
 *  Post: the total income earned is printed to the screen.
 *
 *  Error: Multiple license plates may not be passed in, error message will be given.  Also, an error
 *  message will be printed if you try to rent a car when none are available.  As for the return dates,
 *  the months must be from 1-12, the days must be from 1-31 (some months may only have 30 days, but for the
 *  sake of this program, all months have 31 days).
 */

#include "linkedList.h"
#include "carLists.h"

int main(){
    runListManager();
    return 0;
}
