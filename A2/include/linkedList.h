/*  Andrew Borgan  0945189
 *  Monday, October 17th, 2016
 */
#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__

typedef struct Car{
    int mileage;
    char * returnDate;
    char * plateNumber;
    struct Car * next;
}Car;

/*  createCar
 *
 *  allocates memory for a new car. returns a pointer to the car.
 *
 *  In: plateNumber, mileage, returnDate
 *
 *  Out: pointer to the created car
 *
 *  Post: N/A
 *
 *  Error: must pass in a plate number and a mileage > 0.  Will not create a car
 *  if there is not enough memory left to allocate.
 */
Car * createCar(char plateNumber[], int mileage, char returnDate[]);

/*  printCar
 *
 *  prints out the information for a given car (plateNumber, mileage, and returnDate)
 *
 *  In: carToPrint
 *
 *  Out: N/A
 *
 *  Post: Car information is printed to the screen
 *
 *  Error: won't print null pointer.
 */
void printCar(Car * carToPrint);

/*  printList
 *
 *  Prints an entire linked list using the printCar function
 *
 *  In: listHead
 *
 *  Out: N/a
 *
 *  Post: list is printed to the screen
 *
 *  Error: Won't print an empty list.
 */
void printList(Car * listHead);

/*  addFront
 *
 *  adds a car to the front of a list.
 *
 *  In: list, car toAdd
 *
 *  Out: updated pointer to the head of the list
 *
 *  Post: List length increased by one
 *
 *  Error: N/A
 */
Car * addFront(Car * list, Car * toAdd);

/*  sort
 *
 *  Sorts the car at the top of the list by mileage.
 *
 *  In: list
 *
 *  Out: N/A
 *
 *  Post: top element is sorted into the list
 *
 *  Error: N/A
 */
Car * sort(Car * list);

/*  removeFront
 *
 *  Removes the first element in the list and destroys it.
 *
 *  In: list
 *
 *  Out: pointer to new head of the list
 *
 *  Post: element is removed from list and deleted
 *
 *  Error: N/A
 */
Car * removeFront(Car * list);

/*  removeMiddle
 *
 *  removes a car that is not at the front of the list from the list.
 *
 *  In: plateNumber, list
 *
 *  Out: N/A
 *
 *  Post: item is removed from the list.
 *
 *  Error: if plateNumber is not found, nothing happens
 */
void removeMiddle(char plateNumber[], Car * list);

/*  search
 *
 *  Searches a list for a give plateNumber
 *
 *  In: plateNumber, list
 *
 *  Out: pointer to the element with the matching plateNumber
 *
 *  Post: N/A
 *
 *  Error: N/A
 */
Car * search(char plateNumber[], Car * list);

/*  copyCar
 *
 *  creates a copy of a given car.
 *
 *  In: someCar
 *
 *  Out: pointer to the copy
 *
 *  Post: New car is created.
 *
 *  Error: Can leak memory if old car isn't deleted.
 */
Car * copyCar(Car * someCar);

/*  destroyCar
 *
 *  Frees the memory of a given car.
 *
 *  In: car toDestroy
 *
 *  Out: N/A
 *
 *  Post: Car is destroyed.
 *
 *  Error: N/A
 */
void destroyCar(Car * toDestroy);

/*  destroyList
 *
 *  Destroys an entire list of cars using destroyCar function
 *
 *  In: list
 *
 *  Out: N/A
 *
 *  Post: list is destroyed (freed)
 *
 *  Error: N/A
 */
void destroyList(Car * list);

#endif
