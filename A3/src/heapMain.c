/*       Andrew Borgan  CIS*2520  0945189
 *          Monday, November 7th, 2016
 *
 *  This program reads 200 integers from a file
 *  named f.dat and sorts it using a heap.
 *  The sum of the first three digits is the key.
 *  The program then prints the resulting heap
 *  to the screen for the user to see.
 */

#include <stdio.h>
#include "runHeap.h"

int main(){
    FILE * filePtr;
    filePtr = fopen("assets/f.dat", "r");
    if(filePtr == NULL){
        printf("file not found error.\n");
    }
    else{
        runHeap(filePtr);
        fclose(filePtr);
    }
    return 0;
}
