//
// Created by hayes on 4/22/2022.
//

#include "LinkedList.h"

// Constructs the empty linked list object.
// Creates the head node and sets length to zero.
LinkedList::LinkedList()
{
    head = NULL;
    length = 0;
}

// Inserts an item at the end of the list.
void LinkedList::insert( Element * newElement )
{
    Element* current = head;
    if (head == nullptr) {
        head = newElement;
    }
    else {
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newElement;
    }
    newElement->next = nullptr;
    length++;
}

// Removes an item from the list by item key.
// Returns true if the operation is successful.
bool LinkedList::remove( string Key )
{
    if (head == nullptr) {
        return false;
    }
    Element* current = head;
    while (current->next != nullptr && current->next->key != Key) {
        current = current->next;
    }
    if (current->next->key == Key) {
        Element* temp = current->next;
        current->next = current->next->next;
        delete temp;
        length--;
        return true;
    }
    else {
        return false;
    }
}

// Searches for an item by its key.
// Returns a reference to first match.
// Returns a NULL pointer if no match is found.
Element * LinkedList::get( string Key )
{
    if (head == nullptr) {
        return nullptr;
    }
    Element* current = head;
    while (current->next != nullptr && current->key != Key) {
        current = current->next;
    }
    if (current->key == Key) {
        return current;
    }
    return nullptr;
}

// Displays list contents to the console window.
void LinkedList::printList()
{
    if (length == 0)
    {
        cout << "\n{ }\n";
        return;
    }
    Element * p = head;
    Element * q = head;
    cout << "\n{ ";
    while (q)
    {
        p = q;
        //if (p != head)
        if (p != nullptr)
        {
            cout << p -> key;
            if (p -> next) cout << ", ";
            else cout << " ";
        }
        q = p -> next;
    }
    cout << "}\n";
}

// Returns the length of the list.
int LinkedList::getLength()
{
    return length;
}

// De-allocates list memory when the program terminates.
LinkedList::~LinkedList()
{
    Element* current = head;
    Element* temp;
    while (current != nullptr) {
        temp = current;
        current = current->next;
        delete temp;
    }
    head = current;
    delete head;
}

//*****************************************************************
// End of File
//*****************************************************************
