/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 *
 *  See linkedList.h for function use
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedList.h"

Car * createCar(char plateNumber[], int mileage, char returnDate[])
{
    if (plateNumber == NULL) //all car numbers must have a plateNumber and a mileage greater than 0.
    {
        printf("plateNumber error\n");
        return NULL;
    }
    else if (mileage < 0)
    {
        printf("mileage can not be negative\n");
        return NULL;
    }
    else
    {
        Car * newCar = malloc(sizeof(Car));
        if (newCar == NULL) //check for enough memory to be allocated
        {
            free(newCar);
            return NULL;
        }
        newCar->plateNumber = malloc(sizeof(Car) * strlen(plateNumber));
        if (newCar->plateNumber == NULL)
        {
            free(newCar->plateNumber);
            free(newCar);
            return NULL;
        }
        newCar->returnDate = malloc(sizeof(Car) * strlen(returnDate));
        if (newCar->returnDate == NULL)
        {
            free(newCar->returnDate);
            free(newCar->plateNumber);
            free(newCar);
        }
        strcpy(newCar->plateNumber, plateNumber); //copy values into new car
        strcpy(newCar->returnDate, returnDate);
        newCar->mileage = mileage;
        return newCar;
    }
}

void printCar(Car * carToPrint)
{
    if(carToPrint != NULL) //can't print an empty list
    {
        printf("Plate Number: %s", carToPrint->plateNumber);
        printf("Mileage: %d\n", carToPrint->mileage);
        printf("Return Date: %s\n", carToPrint->returnDate);
    }
    else
    {
        printf("Error: invalid car\n\n");
    }
}

void printList(Car * listHead)
{
    Car * tempPtr = listHead;
    int count = 1;
    while(tempPtr != NULL) //print until end of list is reached
    {
        printf("Car %d:\n", count);
        printCar(tempPtr);
        tempPtr = tempPtr->next;
        count+=1;
    }
}

Car * addFront(Car * list, Car * newCar)
{
    if (newCar != NULL)//don't add an empty car
    {
        newCar->next = list;
        list = newCar;
    }
    return list;
}

Car * removeFront(Car * list)
{
    if (list != NULL) //can't remove from an empty list
    {
        Car * tempPtr = list;
        tempPtr = tempPtr->next;
        destroyCar(list);
        return tempPtr;
    }
    return NULL;
}

void removeMiddle(char plateNumber[], Car * list)
{
    if (list != NULL)
    {
        Car * tempPtr = list->next;
        Car * tempPtr2 = list;
        while(tempPtr->plateNumber != plateNumber) //find specific car
        {
            tempPtr = tempPtr->next; //remove the item
            tempPtr2 = tempPtr2->next;
        }
        tempPtr2->next = tempPtr->next;
        destroyCar(tempPtr); //destroy removed item
    }
}

Car * sort(Car * list)
{
    if (list->next == NULL)
    {
        return list;
    }
    Car * tempPtr = list;
    Car * tempPtr2 = tempPtr;
    Car * tempPtr3 = tempPtr;
    while(tempPtr->next != NULL)
    {
        tempPtr = tempPtr->next;
        if (tempPtr->mileage < tempPtr2->mileage) //if mileage of next is less than current, swap them
        {
            tempPtr3->next = tempPtr;
            tempPtr2->next = tempPtr->next;
            tempPtr->next = tempPtr2;
            tempPtr3 = tempPtr;
            if (list == tempPtr2)
            {
                list = tempPtr;
            }
            tempPtr = tempPtr->next;
        }
        else
        {
            if(tempPtr3 != tempPtr2)
            {
                tempPtr3 = tempPtr3->next;
            }
            tempPtr2 = tempPtr2->next;
        }
    }
    return list;
}

Car * search(char plateNumber[], Car * list)
{
    Car * tempPtr = list;
    while(tempPtr != NULL)
    {
        if(strcmp(plateNumber, tempPtr->plateNumber) == 0) //find the car in the list and return it
        {
            return tempPtr;
        }
        tempPtr = tempPtr->next;
    }
    return NULL;
}

Car * copyCar(Car * someCar)
{
    Car * copyCar = createCar(someCar->plateNumber, someCar->mileage, someCar->returnDate);
    copyCar->next = NULL;
    return copyCar;
}

void destroyCar(Car * toDestroy)
{
    free(toDestroy->plateNumber);
    free(toDestroy->returnDate);
    free(toDestroy);
}

void destroyList(Car * listHead)
{
    Car * tempPtr = listHead;
    Car * tempPtr2 = tempPtr;
    while (tempPtr != NULL) //destroy until the end of the list is reached
    {
        destroyCar(tempPtr);
        tempPtr2 = tempPtr2->next;
        tempPtr = tempPtr2;
    }
}
