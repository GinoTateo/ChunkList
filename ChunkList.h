//
// Created by Varick Erickson 2/3/2021.
//

#ifndef CHUNKLIST_H
#define CHUNKLIST_H

#include <iostream>

using namespace std;

const int ARRAY_SIZE = 8;

// These error classes are done. No modifications are required.
// See ChunkList_driver.cpp for an example of how they are used.
class InvalidArrayLength{
public:
    string Msg() {
        return "Invalid array length used for constructor.";
    }
};

class IndexOutOfBounds {
public:
    string Msg() {
        return "Index is out of bounds";
    }
};

class IteratorOutOfBounds {
public:
    string Msg() {
        return "Iterator is out of bounds.  Nothing left to iterate over.";
    }
};

class EmptyList {
public:
    string Msg() {
        return "List is empty";
    }
};

// Put your pre/post conditions here.

template<class T>
class ChunkList {
public:
    // Constructors
    ChunkList();
    ChunkList(T arr[], int arrLen);

    // Deconstructor
    ~ChunkList();

    // Add/remove elements
    void Append(T value);
        // Adds value to the end of the list
        // Precondition: T is a value.
        // Postcondition: The value be added to a list
    void Remove(T value);
        // Removes first instance found in list
        // Precondition: T is a value.
        // Postcondition: The value removed from a/the list

    // Stuff to find out about the ChunkList
    int GetLength();
    double LoadFactor();
    bool Contains(T value);

    // Accessing elements
    T GetIndex(int i);
        // Gets index I value
        // Precondition: i is a value between 0 and the list size.
        // Postcondition: The value at index i returned.

    void ResetIterator();
        // Resets iterator variables
        // Precondition: None.
        // Postcondition: The iterator variables set back to the start.
    T GetNextItem();
        // Gets next item in line
        // Precondition: None.
        // Postcondition: The next item from iterNode returned.

    bool IsEmpty();
private:

    // Note we did not need to make this a template
    // since this struct is part of a template class.
    struct Node {
        Node* next;
        int len;
        T values[ARRAY_SIZE];
    };

    Node* head;
    Node* tail;

    // iterator
    Node* iterNode;     // What node are we currently on?
    int arrPos;         // Within the node, what element are we looking at?

    int listLen;        // Total elements
    int numChunks;      // Total chunks/nodes
};

#include "ChunkList.cpp"

#endif //CHUNKLIST_H
