/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 *
 *  This program will take in commnand line arguments to run either carbon.c, ackermann.c, or newton.c.
 *
 *  carbon.c: prints all permutations of the letters c a r b o n (see carbon.h for more details)
 *
 *  ackermann.c: takes in user input and runs the values through ackermanns function (see ackermann.h for more details)
 *
 *  newton.c:  takes in user input and calculates the square root of a number within an accuracy determined by the user both non recursively and recursively
 *  and then compares which method is faster. (See newton.h for more details)
 *
 *  In: int argc, char * argv[].  Accepts only 2 command line arguments (./A1 1 for carbon, ./A1 2 for ackermann, ./A1 3 for newton)
 *
 *  Out: runs the carbon, ackermann, or newton functions as appropriate.
 *
 *  Error:  See README (assignment1/doc) for details on errors.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include "carbon.h"
#include "ackermann.h"
#include "newton.h"

int main(int argc, char * argv[])
{
    if (argc!=2) //if user does not give 2 command line arguments, print error message and exit
    {
        printf("You must enter 2 command line arguements (./A1 and '1' for carbon, '2' for ackermann, or '3' for newton\n");
        return 1;
    }
    else if (*argv[1] == '1') //carbon.c
    {
        carbon(); //see carbon.c or carbon.h
    }
    else if (*argv[1] == '2')//ackermann.c
    {
        char first[500]; //two character arrays used to receive input to send to ackermann function
        char second[500];
        int ans;

        getAckermannInput(first, second);
        ans = ackermann(atoi(first), atoi(second)); //ans is result of ackermann function
        printf("A(%d,%d) is %d\n", atoi(first), atoi(second), ans); //result message for user
    }
    else //newton.c
    {
        double value, errorRange; //for user input
        printf("Enter a value to determine its square root\n");
        value = getInput();
        printf("Enter an acceptable error range (0.1 would mean within + or - 0.1 of true value)\n");
        errorRange = getInput();
        testNewton(value, errorRange); //see newton.c or newton.h
    }

    return 0;
}
