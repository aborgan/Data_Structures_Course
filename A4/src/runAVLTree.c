/*  Andrew Borgan             0945189
 *     Monday, November 28th, 2016
 *  See avlTree.h for function details.
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <ctype.h>
#include "runAVLTree.h"
#include "avlTree.h"

void runAVLTree(){
    int option = 0; //for user input
    avlTree tree; //initialize tree
    tree.root = NULL;
    tree.size = 0;
    treeNode * tempNode; //tempNode is used to temporarily store return values of some functions in avlTree.c
    char temp[100]; //for user input
    int validNum; //validNum is to check if for option 6 the user entered an integer.

    printf("\n");
    printf("******************************************\n");
    printf("      Andrew Borgan        0945189        \n");
    printf("\n");
    printf("   Welcome to the AVL Tree demonstration  \n");
    printf("******************************************\n\n");
    while(option != 7){
        option = getInput();
        switch(option){
            case 1:
                tree = init(tree); //initalize avlTree
                break;
            case 2:
                printf("find key:\n");
                fgets(temp, 100, stdin);
                temp[strlen(temp) - 1] = '\0';
                tempNode = search(tree.root, temp); //find node
                if(tempNode!=NULL){ //node found
                    printf("key: %s frequency: %d\n\n", tempNode->key, tempNode->frequency);
                }
                else{ //node not found
                    printf("node not found\n\n");
                }
                break;
            case 3:
                printf("insert key:\n");
                fgets(temp, 100, stdin);
                temp[strlen(temp) - 1] = '\0';
                createNode(temp);
                tree = addNode(tree, temp); //adding to the tree
                break;
            case 4:
                printf("enter key to delete:\n");
                fgets(temp, 100, stdin);
                temp[strlen(temp) - 1] = '\0';
                tree.root = removeNode(tree.root, temp); //deleting from the tree
                if(tree.size > 0){
                    tree.size-=1;
                }
                break;
            case 5:
                if(tree.root != NULL){ //not an empty tree.
                    printf("height %d size: %d\n\n", tree.root->height, tree.size);
                }
                else{
                    printf("tree is empty\n");
                }
                break;
            case 6:
                validNum = 1;
                printf("enter frequency:\n");
                fgets(temp, 100, stdin);
                temp[strlen(temp) - 1] = '\0';
                for(int i = 0; i < strlen(temp); i+=1){
                    if(!isdigit(temp[i])){
                        validNum = 0;
                        break; //invalid number
                    }
                }
                if(validNum){
                    printf("The following values have a frequency greater than %d:\n", atoi(temp));
                    findAllAboveFrequency(tree.root, atoi(temp));
                    printf("\n");
                }
                else{
                    printf("Invalid number\n\n");
                }
                break;
            case 7:
                break; //quit
            default:
                    printf("unexpected error\n"); //should never occur
                break;
        }
    }
    destroyTree(tree.root); //destroy tree when user is done with it
}

int validOption(char input[]){
    if(strlen(input) == 2 && isdigit(input[0]) && atoi(input) > 0 && atoi(input) < 8){ //This is valid input
        return 1;
    }
    else{
        printf("You must enter a 1 digit number between 1 and 7\n");
        return 0;
    }
}

int getInput(){
    char input[100];
    do{
        printf("Select an option (1-7):\n");
        printf("1. Initialization\n");
        printf("2. Find\n");
        printf("3. Insert\n");
        printf("4. Remove\n");
        printf("5. Check Height and Size\n");
        printf("6. Find All (above a given frequency)\n");
        printf("7. exit\n");
        fgets(input, 100, stdin);
    }while(!validOption(input)); //keep looping until valid input is given
    return atoi(input); //return valid input
}

avlTree init(avlTree tree){
    char temp[100];
    FILE * fptr;

    printf("Enter the file path:\n");
    fgets(temp, 100, stdin);
    temp[strlen(temp) - 1] = '\0';
    fptr = fopen(temp, "r");
    if(fptr == NULL){
        printf("File Not Found.  Ensure path specified is correct\n");
        return tree;
    }
    while(fscanf(fptr, "%s", temp) != EOF){ //scan each word in and add it to the tree
        tree = addNode(tree, temp);
    }

    fclose(fptr);
    return tree;
}

avlTree addNode(avlTree tree, char key[]){
    if(tree.root == NULL){ //only used to initialize the tree (if it's empty).  All other things are inserted
        tree.root = createNode(key);
        tree.root->frequency = 1;
        tree.root->height = 1;
        tree.size+=1;
    }
    else{
        treeNode * newNode = createNode(key); //create node and add it to the tree.
        tree = insert(tree, newNode);
    }
    return tree;
}
