/*  Andrew Borgan  CIS*2520  0945189
 *     Monday, November 7th, 2016
 */

#ifndef __ABORGAN_MATHTREE__
#define __ABORGAN_MATHTREE__

#include <stdbool.h>
#include "tree.h"

/*  runTree
 *
 *  This function runs the bulk of the program.  It constructs
 *  the tree from the input given by the user.  It then loops
 *  through and calls other functions depending on the users input.
 *
 *  In:  char input[]
 *
 *  Out:  Program ends when this function ends
 */
void runTree(char input[]);

/*  getInput
 *
 *  Gets the users input for the menu of the
 *  program.  It will only return if the user gives valid input (int from 1-7).
 *
 *  Out:  Returns the integer value of the user input
 */
int getInput();

/*  validMath
 *
 *  Performs a simple check to ensure that the user is giving valid input.
 *  If the input is invalid, the program will exit.
 *
 *  In:  char input[]
 *
 *  Out:  Main loop begins if true, program ends otherwise. 
 */
bool validMath(char input[]);

/*  makeTree
 *
 *  Creates the tree based on the user input and stores values in all of it's nodes.
 *
 *  In: input[], numNodesPtr, nodeDepth
 *
 *  Out: Nodes are all filled with information and tree is created
 *
 *  Error:  Assumes valid input was given.  Depends on validMath function working properly.
 */
treeNode * makeTree(char input[], int * numNodesPtr, int * nodeDepth);

/*  addNum
 *
 *  Adds a number to the tree
 *
 *  In: input[], i, leftBranch, current
 *
 *  Out:  returns updated i value to makeTree function.
 */
int addNum(char input[], int i, bool leftBranch, treeNode * current);

/*  addVar
 *
 *  Adds a variable to the tree
 *
 *  In: input[], i, leftBranch, current
 *
 *  Out:  returns updated i value to makeTree function.
 */
int addVar(char input[], int i, bool leftBranch, treeNode * current);

#endif
