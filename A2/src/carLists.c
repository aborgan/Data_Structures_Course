
/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 *
 *  See carLists.h for function usage
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "linkedList.h"
#include "carLists.h"

void runListManager(){

    printf("Welcome to the rental car list manager\n");

    Car * availableForRentHead = NULL; //head of the three linked lists
    Car * rentedHead = NULL;
    Car * inRepairHead = NULL;

    FILE * listFile;

    listFile = fopen("assets/list", "r");
    if (listFile == NULL)
    {
        printf("No list found, starting with no list\n");
    }
    else
    {
        char junk[100];
        fgets(junk, 100, listFile);
        availableForRentHead = loadList(listFile, availableForRentHead, "Rented:\n");
        rentedHead = loadList(listFile, rentedHead, "inRepair:\n");
        inRepairHead = loadList(listFile, inRepairHead, "\n");
        fclose(listFile);
        printf("a previous list has been found and loaded\n");
    }
    int option = 0; //used to track what user wants to do
    char tempPlateNumber[100]; //stores a temporary plate number to be passed to other functions
    char * tempReturnDate;
    int tempMileage; //other temporary variables
    double totalIncome = 0.0; //tracks total profit made for when the user quits the program
    Car * carSearch; //temporary pointers for handling moving cars from one list to another
    Car * carCopy;

    while (option != 7) //7 means quit
    {
        option = getValidOption();
        switch(option){
            case 1: //adds a new car to the available for rent list.
                printf("Enter the plate number:\n");
                fgets(tempPlateNumber, 100, stdin);
                carSearch = search(tempPlateNumber, availableForRentHead);
                if (carSearch == NULL) //ensuring only one intance of a plate number can exist (duplicate license plates don't make sense)
                {
                    carSearch = search(tempPlateNumber, rentedHead);
                    if (carSearch == NULL)
                    {
                         carSearch = search(tempPlateNumber, inRepairHead);
                         if (carSearch == NULL)
                         {
                             tempMileage = addMileage();

                             Car * newCar = createCar(tempPlateNumber, tempMileage, "N/A\n");
                             availableForRentHead = addFront(availableForRentHead, newCar);
                             printf("The following car has been added to the available-for-rent list:\n");
                             printCar(availableForRentHead);
                             availableForRentHead = sort(availableForRentHead); //sorts cars from lowest mileage to highest mileage
                             break;
                         }
                    }
                }
                printf("A car with that plate number already exists.\n");
                break;
            case 2: //adds a returned car (has been rented at least once) to the available-for-rent list.
                printf("Enter the plate number:\n");
                fgets(tempPlateNumber, 100, stdin);
                carSearch = search(tempPlateNumber, rentedHead);
                if (carSearch == NULL) //non existant license plate entered
                {
                    printf("A car with that license plate has not been rented\n");
                }
                else //return car
                {
                    totalIncome = calculateCost(totalIncome, carSearch->mileage, carSearch);
                    carCopy = copyCar(carSearch); //makes a copy of the car to pass to the available-for-rent list (original record is freed)
                    strcpy(carCopy->returnDate, "N/A\n"); //delete return date
                    availableForRentHead = addFront(availableForRentHead, carCopy);
                    if (carSearch != rentedHead) //if not at the beginning of the list
                    {
                        removeMiddle(carSearch->plateNumber, rentedHead);
                    }
                    else
                    {
                        rentedHead = removeFront(rentedHead);
                    }

                    printf("The Following car was moved from the rented list to the available-for-rent list:\n");
                    printCar(availableForRentHead);
                    availableForRentHead = sort(availableForRentHead);
                }
                break;
            case 3: //similar logic to case to, except returning car to the repair list instead of available-for-rent list
                printf("Enter the plate number:\n");
                fgets(tempPlateNumber, 100, stdin);
                carSearch = search(tempPlateNumber, rentedHead);
                if (carSearch == NULL)
                {
                    printf("A car with that license plate has not been rented\n");
                }
                else
                {
                    totalIncome = calculateCost(totalIncome, carSearch->mileage, carSearch);
                    carCopy = copyCar(carSearch);
                    strcpy(carCopy->returnDate, "N/A\n"); //delete return date
                    inRepairHead = addFront(inRepairHead, carCopy);
                    if (carSearch != rentedHead)
                    {
                        removeMiddle(carSearch->plateNumber, rentedHead);
                    }
                    else
                    {
                        rentedHead = removeFront(rentedHead);
                    }

                    printf("The Following car was moved from the rented list to the repair list:\n");
                    printCar(inRepairHead);
                    inRepairHead = sort(inRepairHead);
                }
                break;
            case 4: //move car from in repairs list to available-for-rent list
                printf("Enter the plate number:\n");
                fgets(tempPlateNumber, 100, stdin);
                carSearch = search(tempPlateNumber, inRepairHead);
                if (carSearch == NULL) //non existant plate
                {
                    printf("A car with that license plate has not been rented\n");
                }
                else //found the car
                {
                    carCopy = copyCar(carSearch);
                    availableForRentHead = addFront(availableForRentHead, carCopy);
                    if (carSearch != inRepairHead)
                    {
                        removeMiddle(carSearch->plateNumber, inRepairHead);
                    }
                    else
                    {
                        inRepairHead = removeFront(inRepairHead);
                    }

                    printf("The Following car was moved from the repair list to the available-for-rent list:\n");
                    printCar(availableForRentHead);
                    availableForRentHead = sort(availableForRentHead);
                }
                break;
            case 5: //rents a car
                if (availableForRentHead != NULL) //if there is a car availale to be rented
                {
                    tempReturnDate = addReturnDate(); //adds expected return date given by user
                    strcpy(availableForRentHead->returnDate, tempReturnDate);
                    Car * tempPtr = copyCar(availableForRentHead);
                    rentedHead = addFront(rentedHead, tempPtr);
                    rentedHead = sort(rentedHead);
                    availableForRentHead = removeFront(availableForRentHead);
                    printf("The following car has been moved from the available-for-rent list to the rented list:\n");
                    printCar(rentedHead);
                }
                else //no cars to rent
                {
                     printf("There are no cars available\n");
                }
                break;
            case 6: //prints all three list
                if(availableForRentHead != NULL) //print if non-empty
                {
                    printf("\navailable-for-rent list:\n");
                    printList(availableForRentHead);
                }
                else
                {
                    printf("\nno cars in the available-for-rent list\n");
                }
                if(rentedHead != NULL)
                {
                    printf("\nrented List:\n");
                    printList(rentedHead);
                }
                else
                {
                    printf("\nno cars in the rented list\n");
                }
                if(inRepairHead != NULL)
                {
                    printf("\nrepair list:\n");
                    printList(inRepairHead);
                }
                else
                {
                    printf("\nNo cars in the repair list\n\n");
                }
                break;
            case 7: //quits
                break;
            default: //all other input is an error
                printf("You must pick an option between 1 and 7");
                break;
        }
    }
    printf("\nThank you for using the rental car list manager! The total income was $%.2lf\n", totalIncome);
    listFile = fopen("assets/list", "w");
    fprintf(listFile, "Available-For-Rent:\n");
    if (availableForRentHead != NULL) //if there is a list to use to fill file, fill file with list
    {
        saveList(listFile, availableForRentHead);
    }
    fprintf(listFile, "Rented:\n");
    if (rentedHead != NULL)
    {
        saveList(listFile, rentedHead);
    }
    fprintf(listFile, "inRepair:\n");
    if (inRepairHead != NULL)
    {
        saveList(listFile, inRepairHead);
        fprintf(listFile, "\n");
    }
    else
    {
        fprintf(listFile, "\n"); //catch to make sure file is readable next time it is loaded (needs the extra nextline)
    }
    fclose(listFile);
    destroyList(availableForRentHead);
    destroyList(rentedHead);
    destroyList(inRepairHead);
}

int getValidOption()
{
    char input[100];

    while (true) //loops until valid input is returned
    {
        printf("Please enter option 1-7\n");
        printf("(1) add a new car to the available-for-rent list\n");
        printf("(2) add a returned car to the available-for-rent list\n");
        printf("(3) add a returned car to the repair list\n");
        printf("(4) transfer a car from the repair list to the available-for-rent list\n");
        printf("(5) rent the first available car\n");
        printf("(6) print all the lists\n");
        printf("(7) quit\n");

        fgets(input, 100, stdin);
        if (strlen(input) != 2) //longer than a single integer
        {
            printf("You must input a single integer between 1 and 7 to select an option\n\n");
        }
        else if(isdigit(input[0]) == 0) //not an integer
        {
            printf("You must input a single integer between 1 and 7 to select an option\n\n");
        }
        else //valid input
        {
            return atoi(input);
        }
    }

}

int addMileage()
{
    char mileage[100];
    while(true) //loops until valid input is returned
    {
        bool check = true;
        printf("Enter the mileage:\n");
        fgets(mileage, 100, stdin);
        for (int i = 0; i < strlen(mileage) - 1; i+=1) //check input for only digits
        {
            if (isdigit(mileage[i]) == 0) //if not a digit
            {
                check = false; //bad input
            }
        }
        if (check == true)
        {
            return atoi(mileage);
        }
        else
        {
            printf("You must enter an integer value\n");
        }
    }
}

char * addReturnDate()
{
    char returnDate[100];
    char * returnDatePtr = returnDate;
    char temp[2]; //check to make sure month and day make sense
    while(true)
    {
        bool check = true;
        printf("Enter the return date (yymmdd):\n");
        fgets(returnDate, 100, stdin);
        if (strlen(returnDate) != 7)
        {
            printf("You must enter the date in the form yymmdd\n");
        }
        else
        {
            for (int i = 0; i < 6; i+=1)
            {
                if (isdigit(returnDate[i]) == 0) //if not a digit, invalid input
                {
                    check = false;
                }
            }
            if (check == true)
            {
                temp[0] = returnDate[2];
                temp[1] = returnDate[3];
                printf("month: %d\n", atoi(temp));
                if (atoi(temp) <= 12 && atoi(temp) > 0) //check for valid month
                {
                    temp[0] = returnDate[4];
                    temp[1] = returnDate[5];
                    printf("day: %d\n", atoi(temp));
                    if (atoi(temp) <= 31 && atoi(temp) > 0) //check for valid day (although a few months don't have 31 days)
                    {
                        return returnDatePtr;
                    }
                }
            }
            printf("You must enter the date in the form yymmdd\n");
        }
    }
}

double calculateCost(double totalIncome, int oldMileage, Car * carSearch)
{
    int newMileage, totalMileage = 0;
    double cost;

    while (oldMileage > newMileage) // rejects a lower new mileage
    {
        newMileage = addMileage();
        if (newMileage < oldMileage)
        {
            printf("Your new mileage can't be less than your old mileage!\n");
        }
    }
    carSearch->mileage = newMileage; //update mileage
    totalMileage = newMileage - oldMileage;
    if (totalMileage > 100)
    {
        totalMileage-=100;
        cost = 40.00 + (0.15*totalMileage);
        totalIncome+=cost;
        totalMileage+=100;
    }
    else
    {
        cost = 40.00;
        totalIncome+=cost;
    }
    printf("The cost of renting the car is a $40.00 flat rate and an additional 15 cents per kilometer (beyond 100km)\n");
    printf("You drove a total of %d kilometers which comes to a total of $%.2lf\n\n\n", totalMileage, cost);

    return totalIncome;
}

Car * loadList(FILE * listPtr, Car * list, char toStop[])
{
    char temp[100];
    char tempPlateNumber[100];
    char tempMileage[100];
    char tempReturnDate[100];
    int count2 = 0;

    while(strcmp(fgets(temp, 100, listPtr), toStop) != 0)
    {
        bool check = false;
        int count = 0;
        if (count2 == 0)
        {
            for (int i = 0; i < strlen(temp); i+=1) //fills plateNumber
            {
                if (check == true)
                {
                    tempPlateNumber[count] = temp[i];
                    count+=1;
                    tempPlateNumber[count] = '\0';
                }
                if (temp[i] == '=')
                {
                    check = true;
                }
            }
        }
        else if (count2 == 1)
        {
            for (int i = 0; i < strlen(temp); i+=1) //fills mileage
            {
                if (check == true)
                {
                    tempMileage[count] = temp[i];
                    count+=1;
                }
                if (temp[i] == '=')
                {
                    check = true;
                }
            }
            tempMileage[strlen(tempMileage)] = '\0';
        }
        else
        {
            for (int i = 0; i < strlen(temp); i+=1) //fills returnDate
            {
                if (check == true)
                {
                    tempReturnDate[count] = temp[i];
                    count+=1;
                    tempReturnDate[count] = '\0';
                }
                if (temp[i] == '=')
                {
                    check = true;
                }
            }
        }
        count2+=1;
        if(count2 > 2) //make completed car, add to list and sort
        {
            count2 = 0;
            Car * newCar = createCar(tempPlateNumber, atoi(tempMileage), tempReturnDate);
            list = addFront(list, newCar);
            list = sort(list);
        }
    }
    return list;
}

void saveList(FILE * filePtr, Car * list)
{
    Car * tempPtr = list;
    while(tempPtr != NULL)
    {
        fprintf(filePtr, "plateNumber=%smileage=%d\nreturnDate=%s", tempPtr->plateNumber, tempPtr->mileage, tempPtr->returnDate);//save car and move to next
        tempPtr = tempPtr->next;
    }
}
