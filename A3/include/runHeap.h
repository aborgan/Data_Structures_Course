/*   Andrew Borgan     CIS*2520     0945189
 *          Monday, November 7th, 2016
 */


#ifndef __ABORGAN_RUNHEAP__
#define __ABORGAN_RUNHEAP__

#include <stdbool.h>

/*  runHeap
 *
 *  This function runs the program and calls the other function.  It reads the file
 *  and uses a downheap algorithm to sort the heap, and then prints the heap to the screen
 *
 *  In:  a pointer to the f.dat file
 *
 *  Out: prints heap to the screen
 *
 *  Error: The functions assumes the f.dat file is in the correct format (200 two digit ints
 *  delimited by a single space).  Function would probably seg-fault otherwise
 */
void runHeap(FILE * filePtr);

/*  getKey
 *
 *  This function returns the key for a given element in the heap (sum of first three digits
 *  of the array)
 *
 *  In: int array[]
 *
 *  Out: key of the array
 */
int getKey(int array[]);

/*  swap
 *
 *  This function swaps two elements in the heap.
 *
 *  In: arrayX, arrayY
 *
 *  Out: arrays are swapped in the heap.
 */
void swap(int arrayX[], int arrayY[]);

/*  external
 *
 *  This function returns true if a node is external.
 *
 *  In: int node
 *
 *  Out: true if external, false otherwise.
 *
 *  Error:  Assumes a heap with 20 elements (given in the assignments specs)
 *  Will break otherwise.
 */
bool external(int node);

#endif
