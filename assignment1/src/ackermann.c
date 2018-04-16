/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 *
 *  See ackermann.h for function details and usage
 */


#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int ackermann(int m, int n)
{
    if (m == 0) //if m = 0, A(m,n) = n + 1.  This is exit condition for recursive function
    {
        return n + 1;
    }
    else if (n == 0) //if n = 0, A(m,n) = A(m-1, 1).  Function calls itself.
    {
        return ackermann(m-1, 1);
    }
    else //if m,n > 0, A(m.n) = A(m-1,A(m,n-1)).  Function calls iself twice.
    {
        return ackermann(m-1, ackermann(m, n-1));
    }
}

void getAckermannInput(char first[], char second[])
{
    bool errCheck, errCheck2 = false;

    printf("Ackermann's function\n\n");
    while (!errCheck) //only exits when user enters acceptable input (0 or a positive integer)
    {
        printf("Please enter the first integer value:\n");
        scanf("%s", first);
        for (int i = 0; i < strlen(first); i+=1) //iterating through string for invalid input
        {
            if (isdigit(first[i]) == 0) //invalid input if anything other than digits 0-9 are found
            {
                errCheck2 = true;
            }
        }
        if (errCheck2 == false)
        {
            if (atoi(first) < 0) //catch for if the integer given overflows the int type and produces a negative number as a result
            {
                printf("You entered a number that is too large.  Your number must be less than 2147483647\n");
            }
            else
            {
                errCheck = true; //valid input
            }
        }
        else //if invalid input was given
        {
            printf("You must enter an integer value greater than 0\n");
            errCheck2 = false;
        }
    }

    errCheck = false; //reset and repeat to receive the second value from the user
    errCheck2 = false;

    while (!errCheck) //similar logic is used to the first loop.  Refer to line 35
    {
        printf("Please enter the second integer value:\n");
        scanf("%s", second);
        for (int i = 0; i < strlen(second); i+=1)
        {
            if (isdigit(second[i]) == 0)
            {
                errCheck2 = true;
            }
        }
        if (errCheck2 == false)
        {
            if (atoi(second) < 0)
            {
                printf("You entered a number that is too large.  Your number must be less than 2147483647\n");
            }
            else
            {
                errCheck = true;
            }
       }
        else
        {
            printf("You must enter an integer value greater than 0\n");
            errCheck2 = false;
        }
    }
}
