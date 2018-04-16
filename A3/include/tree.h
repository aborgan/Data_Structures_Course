/*  Andrew Borgan  CIS*2520  0945189
 *    Monday, November 7th, 2016
 */

#ifndef __ABORGAN_TREE__
#define __ABORGAN_TREE__

#include <stdbool.h>

typedef struct treeNode{
    struct treeNode * parent;
    struct treeNode * leftChild;
    struct treeNode * rightChild;
    int depth;
    int leftness; //how far to the left in the tree a node is (based on depth)
    char * data;
}treeNode;

/*  createNode
 *
 *  Creates a new node for the tree and fills it with data.
 *
 *  In: data[]
 *
 *  Out:  Pointer to new node.
 *
 *  Error:  May return null if memory is not successfully allocated.
 */
treeNode * createNode(char data[]);

/*  isEmpty
 *
 *  Checks if the tree is empty.  True if empty
 *
 *  In: root
 *
 *  Out: true if empty false otherwise
 */
bool isEmpty(treeNode * root);

/*  addNodeLeft
 *
 *  Creates a new node and adds it to the left of the parent node.
 *
 *  In: parent, data
 *
 *  Out: pointer to the new node
 */
treeNode * addNodeLeft(treeNode * parent, char data[]);

/*  addNodeRight
 *
 *  Similar to addNodeLeft, except it creates the new node as the rightChild of the parent
 */
treeNode * addNodeRight(treeNode * parent, char data[]);

/*  updateNode
 *
 *  Updates a node with a new data value
 *
 *  In: current, data
 *
 *  Out: node is updated.
 */
void updateNode(treeNode * current, char data[]);

/*  inOrder
 *
 *  Performs a traversal of the tree "inOrder".  Prints results to the screen for the user
 *
 *  In: root
 *
 *  Out:  Prints inOrder traversal to the screen
 */
void inOrder(treeNode * root);

/*  preOrder
 *
 *  Performs a "preOrder" traversal of the tree. Similar to inOrder
 */
void preOrder(treeNode * root);

/*  postOrder
 *
 *  performs a "postOrder" traversal of the tree. Similar to inOrder and preOrder.
 */
void postOrder(treeNode * root);

/*  update
 *
 *  Locates a variable in the tree based on user input and updates it based on user input.
 *
 *  In: root, data[], numNodes, nodeCount
 *
 *  Out:  variable is updated.
 */
void update(treeNode * root, char data[], int numNodes, int nodeCount);

/*  validUpdate
 *
 *  Checks to see if the value the user is attempting to update a variable with is valid.
 *
 *  In: temp
 *
 *  Out: true if valid input (integer or float).  Otherwise false
 */
bool validUpdate(char temp[]);

/*  Calculate
 *
 *  Determines the value of the arithmetic tree.
 *
 *  In: root
 *
 *  Out:  Prints the results of the tree to the screen for the user.
 *
 *  Error: Catches divide by zero error and will not print result.
 */
float calculate(treeNode * root);

/*  printTree
 *
 *  dislays the tree for the user to see.
 *
 *  In: root, nodeDepth, leftness
 *
 *  Out:  displays tree for user
 *
 *  Error:  Assumes all numbers are 4 characters long and all variables are 2 characters long.  Otherwise the display won't be centered properly
 */
void printTree(treeNode * root, int nodeDepth, int leftness);

/*  search
 *
 *  Searches for a node based on its position in the tree.  Returns a pointer to the node if found, NULL otherwise.
 *
 *  In: root, depth, lefness
 *
 *  Out: pointer to found node, or NULL
 */
treeNode * search(treeNode * root, int depth, int leftness);

#endif
