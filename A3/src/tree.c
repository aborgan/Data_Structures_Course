/*  Andrew Borgan  CIS*2520  0945189
 *     Monday, November 7th, 2016
 *
 *  See tree.h for function details
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include "tree.h"

treeNode * createNode(char data[]){
    if(data == NULL){ //data can't be null
        printf("Error.  Data NULL\n");
        return NULL;
    }
    treeNode * newNode = malloc(sizeof(treeNode));
    if(newNode == NULL){ //malloc memory error
        printf("Not enough memory\n");
        return NULL;
    }
    newNode->data = malloc(sizeof(char) * 5);
    if(newNode->data == NULL){ //memory error
        printf("Not enough memory\n");
        return NULL;
    }
    strcpy(newNode->data, data); //if no error, initialize all values
    newNode->parent = NULL;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

bool isEmpty(treeNode * root){
    if(root == NULL){ //true if no tree exists
        return true;
    }
    return false;
}

treeNode * addNodeLeft(treeNode * parent, char data[]){
    if(isEmpty(parent)){ //if empty, just add as root
        treeNode * newNode;
        newNode = createNode(data);
        return newNode;
    }
    else{ //add left otherwise
        treeNode * newNode = parent->leftChild;
        newNode = createNode(data);
        newNode->parent = parent;
        parent->leftChild = newNode;
        return newNode;
    }
}

treeNode * addNodeRight(treeNode * parent, char data[]){
    if(isEmpty(parent)){ //if empty, just add as root
        treeNode * newNode;
        newNode = createNode(data);
        return newNode;
    }
    else{ //add right otherwise
        treeNode * newNode = parent->rightChild;
        newNode = createNode(data);
        newNode->parent = parent;
        parent->rightChild = newNode;
        return newNode;
    }
}

bool isExternal(treeNode * someNode){ //true if current node is a leaf
    if(someNode->leftChild == NULL && someNode->rightChild == NULL){
        return true;
    }
    return false;
}

void updateNode(treeNode * current, char data[]){
    strcpy(current->data, data); //load new data into node
}

void inOrder(treeNode * root){
    if(root->leftChild != NULL){ //visit left first
        printf("(");
        inOrder(root->leftChild);
    }
    printf("%s", root->data); //then parent
    if(root->rightChild != NULL){ //then right last
        inOrder(root->rightChild);
        printf(")");
    }
}

void preOrder(treeNode * root){
    printf("%s", root->data); //visit parent first
    if(root->leftChild != NULL){ //then left
        preOrder(root->leftChild);
    }
    if(root->rightChild != NULL){ //then right last
        preOrder(root->rightChild);
    }
}

void postOrder(treeNode * root){
    if(root->leftChild != NULL){ //visit left first
        postOrder(root->leftChild);
    }
    if(root->rightChild != NULL){ //then right
        postOrder(root->rightChild);
    }
    printf("%s", root->data); //then parent last
}

void update(treeNode * root, char data[], int numNodes, int nodeCount){
    char temp[100]; //to store value to update node with
    if(strcmp(root->data, data) == 0){ //found the Node the user is searching for
        printf("Variable found.  Enter the value of the variable\n");
        do{
            fgets(temp, 100, stdin);
            temp[strlen(temp) - 1] = '\0';
            if(!validUpdate(temp)){
                printf("invalid value.  Must be a 4 digit int or a 3 digit float\n");
            }
        }while(!validUpdate(temp)); //get input until it's valid input
        strcpy(root->data, temp); //update the node
    }
    else{ //if not currently at the correct node
        if(root->leftChild != NULL){ //visit left child
            update(root->leftChild, data, numNodes, nodeCount+1);
        }
        if(root->rightChild != NULL){ //visit right child
            update(root->rightChild, data, numNodes, nodeCount+1);
        }
        treeNode * tempPtr = root; //checks to see if the current node is the last node
        while(root->parent != NULL){
            root = root->parent;
        }
        while(root->rightChild != NULL){
            root = root->rightChild;
        }
        if(tempPtr == root){ //if it is the last node and there is no match, print an error message
            printf("Variable not found\n");
        }
    }
}

bool validUpdate(char temp[]){
    bool countDecimal = 0; //can only have one '.'
    for(int i = 0; i < strlen(temp); i+=1){
        if (strlen(temp) != 4){ //too long
            return false;
        }
        else if(!isdigit(temp[i]) && temp[i] != '.'){//invalid symbols used
            return false;
        }
        else if(temp[i] == '.'){ //found a '.'
            countDecimal+=1;
        }
    }
    if(countDecimal > 1 || temp[3] == '.'){//too many '.'
        return false;
    }
    return true;
}

float calculate(treeNode * root){
    if(isExternal(root)){ //if external node, return a value
        bool containsDecimal = false;
        if(root->data[0] == 'x' || root->data[0] == 'X'){
            return 0.0;
        }
        for(int i = 0; i < strlen(root->data); i+=1){
            if(root->data[i] == '.'){
                containsDecimal = true;
            }
        }
        if(containsDecimal){
            return atof(root->data);
        }
            return (float)atoi(root->data);
    }
    else{ //otherwise, currently at an operator, and must do math
        float x, y;
        x = calculate(root->leftChild); //find the value of the left child
        y = calculate(root->rightChild); //find the value of the right child
        if(root->data[0] == '+'){ //for addition
            if(root->parent == NULL){ //this is the last addition, print total
                printf("Total is %.2f\n", (x+y));
            }
            return x+y;
        }
        else if(root->data[0] == '-'){
            if(root->parent == NULL){ //last operation, print total
                printf("Total is %.2f\n", (x-y));
            }
            return x-y;
        }
        else if(root->data[0] == '*'){
            if(root->parent == NULL){ //last operation, print total
                printf("Total is %.2f\n", (x*y));
            }
            return x*y;
        }
        else{
            if(y == 0.0){
                printf("divide by zero error\n"); //can't divide by zero
            }
            else if(root->parent == NULL){ //last operation, print total
                printf("Total is %.2f\n", (x/y));
            }
            return x/y;
        }
    }
}

void printTree(treeNode * root, int nodeDepth, int leftness){
    for(int depth = 0; depth <= nodeDepth; depth+=1){ //looping for depth
        printf("     ");
        for(int i = 0; i < pow(2, nodeDepth - depth -1) -1; i+=1){ //initial spacing
            printf("      ");
        }
        if(nodeDepth != depth){ //more initial spacing
            printf("   ");
        }
        for(int leftness = 1; leftness <= pow(2,depth); leftness+=1){ //looping for width
            treeNode * foundNode = search(root, depth, leftness); //find if a node at a given position exists.  Print it out if it does and print spaces otherwise
            if(foundNode != NULL){
                if(foundNode->data[0] == '+' || foundNode->data[0] == '-' || foundNode->data[0] =='*' || foundNode->data[0] == '/'){
                    printf("  %c  ", foundNode->data[0]);
                }
                else if(foundNode->data[0] == 'x' || foundNode->data[0] == 'X'){
                    printf(" %s  ", foundNode->data);
                }
                else{
                    printf("%s ", foundNode->data);
                }
            }
            else{ //no node found
                printf("     ");
            }
            for(int i = 0; i < pow(2, nodeDepth - depth) -1; i+=1){ //spacing between nodes
                printf(" ");
                printf("     ");
            }
            printf(" ");
        }
        printf("\n");
    }
}

treeNode * search(treeNode * root, int depth, int leftness){
    treeNode * temp = NULL; //temp used to avoid seg faulting by trying to access root values if root == NULL
    if(root!=NULL){
        if(root->leftness == leftness && root->depth == depth){ //check for match
            return root;
        }
        else{
            if(root->leftChild != NULL){ //go to next node
                temp = search(root->leftChild, depth, leftness);
                if(temp != NULL){ //if match found, this will stop the code from continuing
                    root = temp;
                }
            }
            if(root->leftness == leftness && root->depth == depth){ //check match
                return root;
            }
            if(root->rightChild != NULL){ //similar logic as leftChild
                temp = search(root->rightChild, depth, leftness);
                if(temp != NULL){
                    root = temp;
                }
            }
            if(root->leftness == leftness && root->depth == depth){
                return root;
            }
            return NULL; //node not found
        }
    }
    return NULL; //node not found
}
