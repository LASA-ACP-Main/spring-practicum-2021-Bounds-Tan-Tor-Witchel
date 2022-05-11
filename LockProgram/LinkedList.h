//
// Created by hayes on 4/22/2022.
//

#ifndef LOCKSIMULATION_LINKEDLIST_H
#define LOCKSIMULATION_LINKEDLIST_H

#include <iostream>
#include <string>
using namespace std;

//*****************************************************************
// List Elements are keys with pointers to the next item.
//*****************************************************************
struct Element
{
    string key;
    Element * next;
};

//*****************************************************************
// Linked lists store a variable number of items.
//*****************************************************************
class LinkedList
{
private:
    // Head is a reference to a list of data nodes.
    Element * head;

    // Length is the number of data nodes.
    int length;

public:
    // Constructs the empty linked list object.
    // Creates the head node and sets length to zero.
    LinkedList();

    // Inserts an item at the end of the list.
    void insert( Element * newElement );

    // Removes an Element from the list by item key.
    // Returns true if the operation is successful.
    bool remove( string Key );

    // Searches for an item by its key.
    // Returns a reference to first match.
    // Returns a NULL pointer if no match is found.
    Element * get( string Key );

    // Displays list contents to the console window.
    void printList();

    // Returns the length of the list.
    int getLength();

    // De-allocates list memory when the program terminates.
    ~LinkedList();
};

#endif

//*****************************************************************
// End of File
//*****************************************************************