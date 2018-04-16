/*  Andrew Borgan, Monday September 26th 2016
 *  aborgan@mail.uoguelph.ca
 *
 *  See newton.h for function details and usage
 */

#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>


double newton(double x, double errorRange)
{
    double a, check; // check is used to apply absolute value signs to abs(a*a-x)
    a = x/2;
    check = (a*a) - x;
    if (check < 0)
    {
        check*=-1; //ensure that (a*a) -x is positive to compare to errorRange
    }
    while(check > errorRange) //as long as abs((a*a) - x) > errorRange
    {
        a = (a+(x/a))/2; //apply newton's method
        check = (a*a) - x;
        if (check < 0)
        {
            check*=-1;
        }
    }
    return a; //returs square root of x
}

double newtonRecursive(double x, double a, double errorRange)
{
    double check = (a*a) - x; //similar logic as in newton() function
    if (check < 0)
    {
        check*=-1;
    }
    if (check > errorRange) //as long as abs((a*a) - x) > errorRange
    {
        return newtonRecursive(x, (a+(x/a))/2, errorRange); //function calls itself with new a value
    }
    else
    {
        return a; //returns square root of x
    }
}

void testNewton(double x, double errorRange)
{
    double a = x; //a needed for newtonRecursive function
    double result; //result of square root
    struct timeb initial, final; //used to measure time
    double time1, time2, total1, total2; //used for timer math

    ftime(&initial); //get time
    time1 = (int)initial.time + (double)initial.millitm/1000;
    for (int i = 0; i < 10000000; i+=1) //performs calculation 10000000 times to make sure the calculation takes long enough to time.
    {
        result = newton(x, errorRange);
    }
    ftime(&final);
    time2 = (int)final.time + (double)final.millitm/1000;
    total1 = time2-time1; //total1 is how long the function took to complete 10000000 times
    printf("The square root of %lf is %lf within an error of %lf (non-recursive method)\n", x, result, errorRange);
    printf("The non-recursive method took a total of %lfx10^-7 seconds to compute\n", total1); //x10^-7 accounts for the function complete 1x10^7 times assuming each calculation takes approximately the same amount of time to complete


    ftime(&initial); //similar logic is applied to determine the time it takes to complete the recursive function call
    time1 = (int)initial.time + (double)initial.millitm/1000;
    for (int i = 0; i < 10000000; i+=1)
    {
        result = newtonRecursive(x, a, errorRange);
    }
    ftime(&final);
    time2 = (int)final.time + (double)final.millitm/1000;
    total2 = time2-time1;
    printf("The square root of %lf is %lf within an error of %lf (recursive method)\n", x, result, errorRange);
    printf("The recursive method took a total of %lfx10^-7 seconds to compute\n", total2);
    printf("The recursive method took %lfx10^-7 seconds longer to compute\n", total2-total1); //how much slower recursive function was
    printf("The recursive method takes %lf times as long as the non-recursive method\n", total2/total1); //how many times as long the recursive function took
}

float getInput()
{
    double input = -1.0;
    char line [256];
    int count = 0;

    while (input < 0) //while input is invalid
    {
        fgets(line, 256, stdin);
        for (int i = 0; i < strlen(line) - 1; i+=1) //check through input to determine if it was valid or not
        {
            if(line[i] == '.') //only one . allowed
            {
                count+=1;
            }
            else if(isdigit(line[i]) == 0) //if anything other than a . or a digit, invalid input
            {
                count = -1; //reset input loop
                i = strlen(line);
            }
        }
        if (count == 1 || count == 0) //for valid input
        {
            input = atof(line);
        }
        else //if too many '.' were entered
        {
            printf("You must enter either 0 or a positive real number\n");
            count = 0; //reset input loop
        }
    }

    return input; //returns valid input
}
