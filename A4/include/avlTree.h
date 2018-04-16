/*  Andrew Borgan             0945189
 *     Monday, November 28th, 2016
 */

#ifndef __ABORGAN_AVLTREE__
#define __ABORGAN_AVLTREE__

//struct representing each node in the avl tree
typedef struct treeNode{
    int frequency;
    int height;
    int balanceFactor;
    struct treeNode * parent;
    struct treeNode * leftChild;
    struct treeNode * rightChild;
    char * key;
}treeNode;

typedef struct avlTree{
    treeNode * root;
    int size;
}avlTree;

treeNode * createNode(char key[]);

/*  rotateLeft
 *
 *  Performs a left rotation on a tree at a given node n.
 *
 *  Assumes the tree needs this rotation to occur to be balanced.
 *  To be used when the tree is balancing itself as nodes are inserted
 */
void rotateLeft(treeNode * n);

/*  rotateRight
 *
 *  Performs a right rotation on a tree at a given node n.
 *
 *  Assumes the tree needs this rotation to occur to be balanced.
 *  To be used when the tree is balancing itself as nodes are inserted
 */
void rotateRight(treeNode * n);

/*  rotateLR
 *
 *  Rotates left at n->rightChild, and then right at n
 *  Assumes that the tree needs this rotation to occur.
 *  Assumes the tree is balaning itself with each new node.
 */
void rotateLR(treeNode * n);

/*  rotateRL
 *
 *  Rotates right at n->leftChild, and then left at n
 *  Assumes that the tree needs this rotation to occur.
 *  Assumes the tree is balaning itself with each new node.
 */
void rotateRL(treeNode * n);

/*  insert
 *
 *  inserts node newNode into avlTree tree.  assumes tree isn't empty.
 *  For duplicate keys the tree increases the frequency of that node.
 *  returns the updated tree
 */
avlTree insert(avlTree tree, treeNode * newNode);

/*  adjustHeight
 *
 *  Called by insert.  Ensures that the tree nodes have the correct height
 *  After insertion and balancing occurs.
 *  returns the updated tree root
 */
treeNode* adjustHeight(treeNode * n);

/*  removeNode
 *
 *  removes the node with the given key from the tree and rebalances
 *  and adjusts the tree as necessary.
 *  returns the updated tree root.
 */
treeNode * removeNode(treeNode * root, char key[]);

/*  balance
 *
 *  performs the correct rotations to node n depending on it's balance factor.
 */
void balance(treeNode * n);

/*  search
 *
 *  searches for a node with given key.
 *  returns the node if found, otherwise returns null.
 */
treeNode * search(treeNode * root, char key[]);

/*  findAllAboveFrequency
 *
 *  performs an in order traversal of the tree and prints out all nodes with
 *  frequency above give value.
 */
void findAllAboveFrequency(treeNode * root, int frequency);

/*  destroyNode
 *
 *  frees the memory of a single treeNode.
 *  Assumes n is not null.
 */
void destroyNode(treeNode * n);

/*  destroyTree
 *
 *  frees the memory of entire tree
 */
void destroyTree(treeNode * n);


#endif
