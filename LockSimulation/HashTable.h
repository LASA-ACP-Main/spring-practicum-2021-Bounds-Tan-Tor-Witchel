//
// Created by hayes on 4/22/2022.
//

#ifndef LOCKSIMULATION_HASHTABLE_H
#define LOCKSIMULATION_HASHTABLE_H

#include "LinkedList.h"

//*****************************************************************
// Hash Table objects store a fixed number of Linked Lists.
//*****************************************************************
class HashTable
{
private:

    // Array is a reference to an array of Linked Lists.
    LinkedList * array;

    // Length is the size of the Hash Table array.
    int length;

    // Calculates a hash for the given key.
    int hFunc( string Key );

public:

    // Constructs the empty Hash Table object.
    // Array length is set to 13 by default.
    HashTable( int tableLength = 13 );

    // Adds an item to the Hash Table.
    void insert( Element * );

    // Deletes an Item by key from the Hash Table.
    // Returns true if the operation is successful.
    bool erase( string Key );

    // Returns an item from the Hash Table by key.
    // If the item isn't found, a null pointer is returned.
    Element * get( string Key );

    // Display the contents of the Hash Table to console window.
    void printTable();

    // Prints a histogram illustrating the Item distribution.
    void printHistogram();

    // Returns the number of locations in the Hash Table.
    int getLength();

    // Returns the number of Items in the Hash Table.
    int getNumberOfElements();

    // De-allocates all memory used for the Hash Table.
    ~HashTable();
};

//*****************************************************************
// End of File
//*****************************************************************

#endif //LOCKSIMULATION_HASHTABLE_H
