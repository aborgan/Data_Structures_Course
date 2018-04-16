/*                            Andrew Borgan  CIS*2520  0945189
 *                               Monday, November 7th, 2016
 *
 *  This program takes in a command line argument from the user containing fully parenthesized
 *  math using addition, subtraction, division, and multiplication.  The prgram then puts the
 *  input into an arithmetic tree.  The program then offers 7 options to the user.  1) Display
 *  2) PreOrder Traversal 3) InOrder Traversal 4) PostOrder Traversal 5) Update 6) Calculate
 *  7) Exit.  Based on the users input the function will perform those operations.  Update will
 *  update a variable that was given in by the user in the command line (of the form x1, x2, etc).
 *  Calculate will return the result of the math, and if there are variables, it will assume a value
 *  of 0.0.
 */

#include<stdio.h>
#include"mathTree.h"

int main(int argc, char * argv[]){

    if(argc != 2){
        printf("invalid command line argument\n");
        return 1;
    }
    runTree(argv[1]);
    printf("Program Ending\n");
    return 0;
}
