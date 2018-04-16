/*  Andrew Borgan           0945189
 *    Monday, November 28th, 2016
 *  See avlTree.h for functin details
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avlTree.h"

treeNode * createNode(char key[]){
    if(key == NULL){ //can't create a node with NULL key.
        printf("Key must not be null to create a node\n");
        return NULL;
    }
    treeNode * newNode = malloc(sizeof(treeNode));
    if(newNode == NULL){ //error check for allocating memory
        printf("Not enough memory to create the new node\n");
        return NULL;
    }
    newNode->key = malloc(sizeof(char) * strlen(key));
    if(newNode->key == NULL){
        printf("Not enough memory to create key\n");
        return NULL;
    }
    newNode->frequency = 0; //initlaize all variables for node
    newNode->height = 0;
    newNode->balanceFactor = 0;
    strcpy(newNode->key, key);
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    newNode->parent = NULL;
    return newNode;
}

void rotateLeft(treeNode * n){
    if(n->rightChild->leftChild == NULL){ //adjust height of top node in left rotation
        n->height-=2;
    }
    else{
        n->height = n->rightChild->leftChild->height + 1; //speial case where height doesn't end up decreasing by 2.
    }
    n->balanceFactor = 0; //n becomes balanced.
    if(n->parent!=NULL){ //not dealing with the root.
        if(n->parent->rightChild == n){
            n->parent->rightChild = n->rightChild;
        }
        else{
            n->parent->leftChild = n->rightChild;
        }
        n->rightChild->parent = n->parent;
    }
    else{ //n is the root
        n->rightChild->parent = NULL;
    }
    treeNode * temp; //complete rotation
    temp = n->rightChild;
    if(temp->leftChild != NULL){
        temp->leftChild->parent = n;
    }
    n->rightChild = temp->leftChild;
    temp->leftChild = n;
    n->parent = temp;
}

void rotateRight(treeNode * n){ //code here is symmetrical to the rotate left function.  Just rotating the opposite way
    if(n->leftChild->rightChild == NULL){
        n->height-=2;
    }
    else{
        n->height = n->leftChild->rightChild->height+1;
    }
    n->balanceFactor = 0;
    if(n->parent!=NULL){
        if(n->parent->rightChild == n){
            n->parent->rightChild = n->leftChild;
        }
        else{
            n->parent->leftChild = n->leftChild;
        }
        n->leftChild->parent = n->parent;
    }
    else{
        n->leftChild->parent = NULL;
    }
    treeNode * temp; //completing rotation
    temp = n->leftChild;
    if(temp->rightChild != NULL){
        temp->rightChild->parent = n;
    }
    n->leftChild = temp->rightChild;
    temp->rightChild = n;
    n->parent = temp;
}

void rotateLR(treeNode * n){
    rotateLeft(n->leftChild);
    rotateRight(n);
    n->parent->leftChild->height+=1; //extra height adjustment
}

void rotateRL(treeNode * n){
    rotateRight(n->rightChild);
    rotateLeft(n);
    n->parent->rightChild->height+=1;
}

avlTree insert(avlTree tree, treeNode * newNode){
    if(newNode == NULL || tree.root == NULL){ //trying to insert empty node
        printf("Error trying to pass in an empty node.\n");
        return tree;
    }
    else{
        treeNode * temp = tree.root;
        while(1){
            if(strcmp(newNode->key, temp->key) == 0){ //node already exists in the tree.  Increase it's frequency
                temp->frequency+=1;
                destroyNode(newNode);
                return tree;
            }
            else if(strcmp(newNode->key, temp->key) > 0){ //node doesn't exist in the tree (is right child), create it and add it in the correct location
                if(temp->rightChild == NULL){
                    temp->rightChild = newNode;
                    newNode->parent = temp;
                    newNode->frequency = 1;
                    tree.root = adjustHeight(newNode);
                    tree.size+=1;
                    return tree;
                }
                temp = temp->rightChild; //recursive search for node
            }
            else if(strcmp(newNode->key, temp->key) < 0){ //node doesn't exist and is a left child.
                if(temp->leftChild == NULL){
                    temp->leftChild = newNode;
                    newNode->parent = temp;
                    newNode->frequency = 1;
                    tree.root = adjustHeight(newNode);
                    tree.size+=1;
                    return tree;
                }
                temp = temp->leftChild; //recursive search for node
            }
        }
    }
}

treeNode * adjustHeight(treeNode * n){
    treeNode * temp;
    while(n != NULL){ //while not at the root
        if(n->leftChild == NULL && n->rightChild == NULL){ //leaf node, height is always 1 and balance facttor is always 0
            n->height = 1;
            n->balanceFactor = 0;
        }
        else if(n->leftChild == NULL && n->rightChild != NULL){ //node with only right child
            n->height = n->rightChild->height+1;
            n->balanceFactor = n->rightChild->height - 0;
        }
        else if(n->leftChild != NULL && n->rightChild == NULL){ //node with only left child
            n->height = n->leftChild->height+1;
            n->balanceFactor = 0 - n->leftChild->height;
        }
        else{ //node with two children
            if(n->leftChild->height > n->rightChild->height){
                n->height = n->leftChild->height+1;
            }
            else{
                n->height = n->rightChild->height+1;
            }
                n->balanceFactor = n->rightChild->height - n->leftChild->height;
        }
        temp = n;
        balance(n); //this will perform any rotations necessary if node n isn't balanced
        if(temp->parent != n->parent){ //rotation may offset tree, restart adjustment
            adjustHeight(n);
        }
        temp = n;
        n = n->parent; //move up a node towards the root.
    }
    return temp;
}

treeNode * removeNode(treeNode * root, char key[]){
    treeNode * n = search(root, key); //search the tree for the node to remove.
    if(n == NULL){ //if that node doesn't exist, you can't remove it.
        printf("key does not exist in the tree.\n");
        return root;
    }
    if(n->leftChild == NULL && n->rightChild == NULL){ //if node to remove is a leaf node
        if(n->parent != NULL){
            if(n->parent->leftChild == n){
                n->parent->leftChild = NULL;
            }
            else{
                n->parent->rightChild = NULL;
            }
            root = adjustHeight(n->parent);
        }
        else{
            root = NULL;
        }
        destroyNode(n);
    }
    else if(n->leftChild == NULL){ //if node to remove only has 1 child (right child)
        if(n->parent != NULL){
            if(n->parent->leftChild == n){
                n->parent->leftChild = n->rightChild;
            }
            else{
                n->parent->rightChild = n->rightChild;
            }
            n->rightChild->parent = n->parent;
            root = adjustHeight(n->parent);
            destroyNode(n); //free memory of deleted node
        }
        else{
            root = root->rightChild;
            root->parent = NULL;
            root = adjustHeight(root);
        }
    }
    else if(n->rightChild == NULL){ //if node to remove only has 1 child (left child)
        if(n->parent != NULL){
            if(n->parent->leftChild == n){
                n->parent->leftChild = n->leftChild;
            }
            else{
                n->parent->rightChild = n->leftChild;
            }
            n->leftChild->parent = n->parent;
            root = adjustHeight(n->parent);
            destroyNode(n); //free memory of deleted node
        }
        else{
            root = root->leftChild;
            root->parent = NULL;
            root = adjustHeight(root);
        }
    }
    else{ //node has two children
        treeNode * temp = n;
        temp = temp->rightChild;
        while(temp->leftChild!=NULL){
           temp=temp->leftChild;
        }
        treeNode * temp2 = temp->parent; //creating temporary nodes to ensure that no data is lost.
        if(temp->parent!=n){ //next biggest node doesn't occur as a child of the root
            if(temp->rightChild == NULL){
                temp->parent->leftChild = NULL;
            }
            else{
               temp->parent->leftChild = temp->rightChild;
            }
        }
        if(temp->rightChild != NULL && temp->parent != n){ //next biggest node is a leaf node
            temp->rightChild->parent = temp2;
        }
        else if(temp->rightChild != NULL && temp->parent == n){ //next biggest node has a child on the right
            temp->rightChild->parent = temp;
        }
        if(n->parent != NULL){ //if node being delete is NOT the root
            if(n->parent->leftChild == n){
                n->parent->leftChild = temp;
            }
            else{
                n->parent->rightChild = temp;
            }
            temp->parent = n->parent;
        }
        else{ //if is IS the root
            temp->parent = NULL;
            root = temp;
        }
        if(n->leftChild != NULL){  //this is just completing the deletion and replacement
            n->leftChild->parent = temp;
        }
        if(n->rightChild != NULL && n->rightChild != temp){
            n->rightChild->parent = temp;
            temp->rightChild = n->rightChild;
        }
        temp->leftChild = n->leftChild;
        if(temp2 == n){
            root = adjustHeight(temp);
        }
        else{
            root = adjustHeight(temp2);
        }
        destroyNode(n); //free memory of deleted node
    }
    return root;
}


void balance(treeNode * n){
    if(n->balanceFactor >  1){
        if(n->rightChild->balanceFactor >= 0){
            rotateLeft(n); //unbalanced and needs left rotation
        }
        else{
            rotateRL(n); //unbalanced, needs RL rotation
        }
    }
    else if(n->balanceFactor < -1){
        if(n->leftChild->balanceFactor <= 0){
            rotateRight(n); //unbalanced, needs R rotation
        }
        else{
            rotateLR(n); //unbaanced, needs LR rotation
        }
    }
}

treeNode * search(treeNode * root, char key[]){
    if(root == NULL){
        return NULL; //empty tree
    }
    else if(strcmp(key, root->key) == 0){
        return root; //found node
    }
    else if(strcmp(key, root->key) > 0){
        return search(root->rightChild, key); //keep searching
    }
    else if(strcmp(key, root->key) < 0){
        return search(root->leftChild, key); //keep searching
    }
    return NULL; //node not in the tree
}

void findAllAboveFrequency(treeNode * root, int frequency){
    if(root == NULL){ //empty tree
        printf("None found.  Empty Tree.\n");
        return;
    }
    if(root->leftChild != NULL){ //this is an in order traversal that prints only nodes with a frequency above the value passed in.
        findAllAboveFrequency(root->leftChild, frequency);
    }
    if(root->frequency > frequency){
        printf("key: %s frequency: %d height: %d\n", root->key, root->frequency, root->height);
    }
    if(root->rightChild != NULL){
        findAllAboveFrequency(root->rightChild, frequency);
    }
}

void destroyNode(treeNode * n){
    free(n->key); //free memory at n
    free(n);
}

void destroyTree(treeNode * root){
    if(root == NULL){ //do nothing for empty tree
    }
    else{ //free all memory in the tree
        if(root->leftChild!=NULL){
            destroyTree(root->leftChild);
            destroyNode(root->leftChild);
        }
        if(root->rightChild!=NULL){
            destroyTree(root->rightChild);
            destroyNode(root->rightChild);
        }
    }
}
