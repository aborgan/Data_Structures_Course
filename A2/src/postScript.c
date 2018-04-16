/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 *
 *  See postScript.h for function usage
 */

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "postScript.h"

double stack[1000]; //impementing a stack ADT
int top = 0; //stack tracker

void runPostScript(char argv[])
{
    if (isdigit(argv[0]) == 0 || isdigit(argv[1]) == 0) //first two values must be digits
    {
        printf("fatal error: invalid postscript\n");
        exit(1);
    }

    double total;
    for (int i = 0; i < strlen(argv); i+=1)
    {
        if(isdigit(argv[i]) != 0) //push digits
        {
            push((double)(argv[i] - '0'));
        }
        else
        {
            total = calculate(pop(), pop(), argv[i]); //apply operator to top two values in stack
            push(total); //push the answer to calculation back in the stack
        }
    }
    printf("%.2lf is answer\n", total);
}

void push(double next)
{
    stack[top] = next;
    top+=1;
}

double pop()
{
    if (top == 0) //if the stack is empty, there were too many operators for valid postfix
    {
        printf("fatal error: invalid postscript\n");
        exit(1);
    }
    top-=1;
    return stack[top];
}

double calculate(double first, double second, char operator)
{
    switch(operator){
        case '+':
            return first+second;
            break;
        case '-':
            return first-second;
            break;
        case '*':
            return first*second;
            break;
        case '/':
            if (second != 0)
            {
                return first/second;
            }
            else
            {
                printf("fatal error: divide by zero\n");
                exit(1);
            }
            break;
        default: //if there are any invalid symbols passed into the postfix it is invalid postfix
            printf("fatal error: Invalid postscript\n");
            exit(1);
            break;
    }
}
