/*  Andrew Borgan  CIS*2520  0945189
 *     Monday, November 7th, 2016
 *
 *  See mathTree.h for function details
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "tree.h"
#include "mathTree.h"

void runTree(char input[]){
    if(!validMath(input)){
        exit(2);
    }
    treeNode * root;
    int width = 1; //used for display
    int numNodes, nodeDepth = 0;
    int * numNodesPtr = &numNodes;
    int * nodeDepthPtr = &nodeDepth;
    int option = 0; //for user input
    root = makeTree(input, numNodesPtr, nodeDepthPtr);
    while(option != 7){ //exits when user inputs 7
        char temp[100]; //used for update function
        option = getInput();
        switch(option){
             case 1: //display
                 for(int i = 0; i < nodeDepth; i+=1){
                     width*=2;
                 }
                 width = width + (width*4);
                 printTree(root, nodeDepth, numNodes);
                 break;
             case 2: //preOrder Traversal
                 preOrder(root);
                 printf("\n");
                 break;
             case 3: //inOrder traversal
                 inOrder(root);
                 printf("\n");
                 break;
             case 4: //postOrder traversal
                 postOrder(root);
                 printf("\n");
                 break;
             case 5: //update variable
                 printf("Enter the variable you wish to update\n");
                 do{
                     fgets(temp, 100, stdin);
                     temp[strlen(temp) - 1] = '\0';
                     if(temp[0] != 'x' && temp[0] != 'X'){
                         printf("invalid variable. Must begin with x or X\n");
                     }
                 }while(temp[0] != 'x' && temp[0] != 'X');
                 update(root, temp, numNodes, 1);
                 break;
             case 6: //calculate current value of arithmetic tree
                 calculate(root);
                 break;
             default:
                 break;
        }
    }
}

int getInput(){
    char input[100];

    while(true){
        printf("1. Display\n");
        printf("2. Preorder\n");
        printf("3. InOrder\n");
        printf("4. PostOrder\n");
        printf("5. Update\n");
        printf("6. Calculate\n");
        printf("7. Exit\n");
        printf("Select an option\n");
        fgets(input, 100, stdin);

        if(strlen(input) != 2){
        }
        else if(isdigit(input[0])){
            if(atoi(input) > 0 && atoi(input) < 8){
                return atoi(input); //only returns for valid input
            }
        }
        printf("invalid input.  must be an integer from 1 to 7\n");
    }
}

bool validMath(char input[]){
    for(int i = 0; i < strlen(input); i+=1){
        if(isdigit(input[i]) == 0 && input[i] != '.' && input[i] != '+' && input[i] != '-' && input[i] != '*' && input[i] != '/' && input[i] != 'x' && input[i] != 'X' && input[i] != '(' && input[i] != ')'){
            printf("invalid input.\n"); //invalid symbol in input.
            return false;
        }
    }
    return true;
}

treeNode * makeTree(char input[], int * numNodesPtr, int * nodeDepthPtr){
    treeNode * root = addNodeLeft(NULL, "temp"); //creates and initializes the first node in the tree.
    root->leftness = 1;
    root->depth = 0;
    *numNodesPtr+=1;
    treeNode * temp = root;
    int nodeDepth = 1;
    bool leftBranch = true;
    for(int i = 1; i < strlen(input); i+=1){ //this logic just decides where the input should be added in the tree.
        if(leftBranch == true){
            if(input[i] == '('){ //for (
                temp = addNodeLeft(temp, "\0");
                *numNodesPtr+=1;
                temp->depth = nodeDepth;
                nodeDepth+=1;
                temp->leftness = (temp->parent->leftness*2) - 1;
            }
            else if(isdigit(input[i])){ //for numbers
                i = addNum(input, i, leftBranch, temp);
                *numNodesPtr+=1;
            }
            else if(input[i] == 'x' || input[i] == 'X'){ //for variables
                i = addVar(input, i, leftBranch, temp);
                *numNodesPtr+=1;
            }
            else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'){ //for operators
                temp->data[0] = input[i];
                temp->data[1] = '\0';
                leftBranch = false;
            }
            else{ //for ')'
                temp = temp->parent;
                nodeDepth-=1;
            }
        }
        else{
            if(input[i] == '('){ //for '('
                temp = addNodeRight(temp, "\0");
                leftBranch = true;
                *numNodesPtr+=1;
                temp->depth = nodeDepth;
                nodeDepth+=1;
                temp->leftness = temp->parent->leftness*2;
            }
            else if(isdigit(input[i])){ //for numbers
                i = addNum(input, i, leftBranch, temp);
                *numNodesPtr+=1;
            }
            else if(input[i] == 'x' || input[i] == 'X'){ //for variables
                i = addVar(input, i, leftBranch, temp);
                *numNodesPtr+=1;
            }
            else if(input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/'){ //for operators
                temp->data[0] = input[i];
                temp->data[1] = '\0';
            }
            else{ //for ')'
                temp = temp->parent;
                nodeDepth-=1;
            }
        }
        if(nodeDepth > *nodeDepthPtr){
            *nodeDepthPtr = nodeDepth;
        }
    }
    return root;
}

int addNum(char input[], int i, bool leftBranch, treeNode * current){
    char temp[5];
    int pos = 0;
    int countDecimals = 0; //check to make sure there is only one decimal in the num.  Will exit if more

    while(isdigit(input[i]) || input[i] == '.'){ //load number
        temp[pos] = input[i];
        if(input[i] == 1){
            countDecimals+=1;
        }
        i+=1;
        pos+=1;
    }
    if(countDecimals > 1 || pos > 4){
        printf("Error entering Numbers.  Numbers may only be 4 digits (3 digits if they have a decimal) long\n");
        exit(3);
    }
    temp[pos] = '\0'; //have to add null terminator or tree will break.
    if(leftBranch){ //logic deciding whether to add to the left or to the right.
        addNodeLeft(current, temp);
        current->leftChild->leftness = (current->leftness*2)-1;
        current->leftChild->depth=current->depth + 1;
    }
    else{
        addNodeRight(current, temp);
        current->rightChild->leftness = current->leftness*2;
        current->rightChild->depth = current->depth + 1;
    }
    return (i-1);
}

int addVar(char input[], int i, bool leftBranch, treeNode * current){
    char temp[5];
    int pos = 0; //

    temp[pos] = input[i];
    i+=1;
    pos+=1;
    while(isdigit(input[i])){ //loading data
        temp[pos] = input[i];
        i+=1;
        pos+=1;
    }
    temp[pos] = '\0';//have to add null terminator or tree will break
    if(pos > 2){ //for invalid variables
        printf("Var error.  Var must be of the form xY or xYY (where Y = digit)\n");
        exit(3);
    }
    if(leftBranch){//logic deciding whether to add to the left or right
        addNodeLeft(current, temp);
        current->leftChild->leftness = (current->leftness*2) - 1;
        current->leftChild->depth= current->depth + 1;
    }
    else{
        addNodeRight(current, temp);
        current->rightChild->leftness = current->leftness*2;
        current->rightChild->depth = current->depth + 1;
    }
    return (i-1);
}

