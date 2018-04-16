#ifndef __ABORGAN_RUNAVLTREE__
#define __ABORGAN_RUNAVLTREE__

#include "avlTree.h"

/*  runAVLTree()
 *
 *  This function runs the program by calling to other functions.
 *  When this function ends, the program will end.
 */
void runAVLTree();

/*  getInput
 *
 *  Gets input from the user.  Will continue looping until the user
 *  enters valid input.  Valid input is considered to be a single
 *  digit integer between 1 and 7 (inclusive).
 *
 *  returns the valid input the user has given.
 */
int getInput();

/*  validInput
 *
 *  Checks if the input that the user has given is valid in the main
 *  menu.  Must be a 1 digit number from 1 to 7.
 *
 *  returns true (1) if valid and false (0) if invalid.
 */
int validInput(char input[]);

/*  init
 *
 *  Gets a file name from the user.  If the file path exists, the
 *  file will be opened and read word by word, with each word being
 *  added to the tree.
 *
 *  returns the updated tree
 */
avlTree init(avlTree tree);

/*  addNode
 *
 *  Creates a node based on a character string key, and adds it to the tree.
 *
 */
avlTree addNode(avlTree tree, char key[]);

#endif
