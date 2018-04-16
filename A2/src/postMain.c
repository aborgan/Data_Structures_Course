/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 *
 *  This program is used to take in a postfix string at the command line and calculate its value.
 *  The program prints a double indicating the total of the calculation.  It should also print
 *  error messages for errors such as attempting to divide by zero, or passing in invalid postfix
 *  notation.
 *
 *  In: int argc, char * argv[] (must pass in a single valid command line argument containing a
 *  postfix math problem to be solve using only single digit positive integers and the operators
 *  +, -, *, and /.
 *
 *  Out: prints the answer to the calculation
 *
 *  Post:N/A
 *
 *  Error: will produce error messages for attempting to divide by zero and for passing in invalid postfix
 *  notation.
 */

#include <stdio.h>
#include "postScript.h"

int main(int argc, char * argv[])
{
    if (argc != 2)
    {
        printf("You must enter only one argument after the executable\n");
        return 1;
    }
    else
    {
        runPostScript(argv[1]);
    }
    return 0;
}
