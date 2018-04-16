/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 */


#ifndef __ABORGAN_NEWTON__
#define __ABORGAN_NEWTON__

/*  newton
 *
 *  This function calculates the square root of input x within an error of errorRange.  It does so non-recursively. the initial input is divided by 2 which is
 *  assigned to a temp variable a.  If abs((a*a)-x) >= errorRange given, then a = (a+(x/a))/2.  Repeat this process until abs((a*a)-x) <= errorRange.
 *
 *  In: double x, double errorRange.
 *
 *  Out: the square root of x within an error range of errorRange.
 *
 *  Error: If the error range given is too small (ie 0.00001) then the program will not be able to successfully compute the root within the error range because
 *  of the limitations with the double data type
 */
double newton(double x, double errorRange);

/*  newtonRecursive
 *
 *  This function performs the same operation as newton, except it does so recursively.  See newton() for more information.
 *
 *  In: double x, double a, double errorRange
 *
 *  Out: the square root of x within an error range of errorRange
 *
 *  Error: See newton()
 */
double newtonRecursive(double x, double a, double errorRange);

/*  testNewton
 *
 *  This function calls to newton and newtonRecursive to calculate the square root given by user and times how long each function takes to complete the task
 *  in seconds.  The function then calculates the time difference between the functions.
 *
 *  In: double x, double errorRange
 *
 *  Out: prints information to the screen for the user about how long newton and newtonRecursive took to complete the task and gives the value of the square
 *  root of x.
 *
 *  Error: N/A
 */
void testNewton(double x, double errorRange);

/*  getInput
 *
 *  This function gets the input from the user and error checks to ensure that an acceptable value was entered.  That input can then be passed on to the other
 *  functions in this file.
 *
 *  In: N/A
 *
 *  Out: User input to be passed to other functions.
 *
 *  Error:  Overflow from very large user input may cause unexpected results.
 */
float getInput();

#endif
