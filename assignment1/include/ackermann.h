/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 */

#ifndef __ABORGAN_ACKERMANN__
#define __ABORGAN_ACKERMANN__

/*  ackermann
 *
 *  This function receives 2 positive integers, and then applies the ackermann function to those values recursively.  If m = 0, A(m,n) = n + 1
 *  If n = 0, A(m,n) = A(m-1,1) and if m, n > 0, then A(m,n) = A(m-1,A(m,n-1))
 *
 *  In:  this function takes in two integers: m and n
 *
 *  Out: returns the result of the ackermann function
 *
 *  Error: values of m greater than four produce errors.  Check assignment1/doc for README on specific details for values of m and n that cause errors
 */
int ackermann(int m, int n);


/*  getAckermannInput
 *
 *  This function prompts the user for input two send to the ackermann function.  It ensures that the user is only able to send positive integer values
 *
 *  In: char first[], char second[] (where input for m and n is stored and tested to ensure an int was given)
 *
 *  Out: no return. String values are stored once acceptable input has been given which will be converted to ints using atoi() function and then passed to ackermann()
 *
 *  Error: Strange behaviour may occur if you input very large numbers that cause the int type to overflow.  The program will catch overflow that causes negative
 *  values because they would break the function, but if the overflow is positive, it may produce an incorrect result.
 */
void getAckermannInput(char first[], char second[]);

#endif
