/*  Andrew Borgan             0945189
 *     Monday, November 28th, 2016
 *
 *      Assignment 4:  avl tree.
 *
 *  runs an avl Tree for the user.
 *  Presents 7 options:
 *  1) initalize.  Takes a file name as input
 *     and attempts to open the file and read
 *     in the data and store it as an avlTree.
 *
 *  2) find.  Finds a node in the avlTree and
 *     prints it to the screen.
 *
 *  3) Insert.  Adds a single node to the tree.
 *     If node already exists, it increases that
 *     node's frequency.
 *
 *  4)  Remove.  Remove's a single node from the tree.
 *
 *  5)  Check height and size.  Prints height of tree
 *      and number of nodes in the tree (nodes with
 *      higher frequencies are only counted once).
 *
 *  6)  find all above given frequency.  Takes a number
 *      as input and prints all nodes with a frequency
 *      greater than that number to the screen.
 *
 *  7)  Quit.  exits the program.
 */

#include <stdio.h>
#include "runAVLTree.h"
#include "avlTree.h"

int main(){

    runAVLTree();
    return 0;
}
