/*  Andrew Borgan  CIS*2520  0945189
 *    Monday, November 17th, 2016
 *
 *  See runHeap.h for function details.
 */

#include <stdio.h>
#include "runHeap.h"
#include <stdbool.h>

void runHeap(FILE * filePtr){
    int heap[21][10]; //21 rows to have a "blank" spot in the array to make the math easier
    for(int i = 1; i < 21; i+=1){
        for(int j = 0; j < 10; j+=1){
            fscanf(filePtr, "%d ", &heap[i][j]);
        }
    }

    for(int Node = 10; Node > 0; Node-=1){
        int node = Node;
        while(!external(node)){ //only execute if it's possible to downheap further
            if((node*2)+1 >= 20){ //exception for the last internal node.  Only one leaf to compare
                if(getKey(heap[node]) > getKey(heap[node*2])){
                    swap(heap[node], heap[node*2]);
                    break;
                }
                else{
                    break;
                }
            }
            else{ //otherwise this logic swaps the current node with the child that's lower if it exists.  Otherwise move on to next node.
                if(getKey(heap[node]) <= getKey(heap[node*2]) && getKey(heap[node]) <= getKey(heap[(node*2) + 1])){
                    break;
                }
                else if(getKey(heap[node]) > getKey(heap[node*2]) && getKey(heap[node]) <= getKey(heap[(node*2) + 1])){
                    swap(heap[node], heap[node*2]);
                    node*=2;
                }
                else if(getKey(heap[node]) <= getKey(heap[node*2]) && getKey(heap[node]) > getKey(heap[(node*2) + 1])){
                    swap(heap[node], heap[(node*2) + 1]);
                    node = (node*2)+1;
                }
                else if(getKey(heap[node]) > getKey(heap[node*2]) && getKey(heap[node]) > getKey(heap[(node*2) + 1])){
                    if(getKey(heap[node*2]) >= getKey(heap[(node*2)+1])){
                        swap(heap[node], heap[(node*2)+1]);
                        node = (node*2) + 1;
                    }
                    else{
                        swap(heap[node], heap[node*2]);
                        node*=2;
                    }
                }
            }
        }
    }
    for(int i = 1; i < 21; i+=1){ //printing out the completed heap
        printf("%d.    ", i);
        if(i < 10){
            printf(" ");
        }
        for(int j = 0; j < 10; j+=1){
            printf("%d ", heap[i][j]);
        }
        printf(" |  Key is: %d\n", getKey(heap[i]));
    }
    printf("\n");
}

int getKey(int array[]){
   return(array[0] + array[1] + array[2]);
}

void swap(int arrayX[], int arrayY[]){
   int tempArray[10];
   for(int i = 0; i < 10; i+=1){
       tempArray[i] = arrayX[i]; //swap two elements in the array
       arrayX[i] = arrayY[i];
       arrayY[i] = tempArray[i];
   }
}

bool external(int node){ //returns true if node is external
    if((node*2) > 20){
        return true;
    }
    return false;
}
