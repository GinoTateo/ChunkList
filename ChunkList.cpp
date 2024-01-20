#include "ChunkList.h"

// Default constructor creates an empty Chunklist.
template<class T>
ChunkList<T>::ChunkList() {

    // Empty Chunklist
    head = NULL;
    tail = NULL;

    // Iter Variables
    Node* newNode = new Node();     // For GetLength
    iterNode = newNode;
    arrPos = 0;

    // Book keeping data
    listLen = 0;
    numChunks=0;
}


template<class T>
ChunkList<T>::ChunkList(T *arr, int arrLen) {

    // Empty Chunklist
    head = NULL;
    tail = NULL;

    // Iter Variables
    iterNode = head;
    arrPos = 0;
    listLen = 0;
    numChunks=0;


    // Error handling
    if(arrLen<0) throw InvalidArrayLength();

    // Add to array
    for(int i = 0;i < arrLen;i++ ){
        Append(arr[i]);
    }
}

template<class T>
ChunkList<T>::~ChunkList() {

}

template<class T>
void ChunkList<T>::Append(T value) {
    listLen++;

    // If none exist. Create one
    if(head==NULL){
        Node* newNode = new Node();
        head = newNode;
        tail = newNode;
        iterNode = newNode;
        head->next=NULL;
        head->values[head->len]=value;
        head->len++;
        numChunks++;
    }
    else {
        // If the last list is full. Create a new one
        if (tail->len >= ARRAY_SIZE) {
            Node *newNode = new Node();
            tail->next = newNode;
            tail = newNode;
            tail->next = NULL;
            tail->values[tail->len] = value;
            tail->len++;
            numChunks++;
        }
            // If the current array is not full add the value to it.
        else{
            Node *current = tail;
            int temp = current->len;
            current->values[temp] = value;
            current->len++;
        }
    }
}

template<class T>
void ChunkList<T>::Remove(T value) {

    // Error Checking
    if(head==NULL) throw EmptyList();

    // For iterating throughout the list
    Node *current = head;
    Node *previous = head;
    bool remove = false;

    while(current!=NULL&&!remove){          // if the chunk isnt null and we havent removed it
        if(current->len<1) throw EmptyList();
        int i = 0;
        while(i<current->len&&!remove) {        // if we havent iterated through the array and removed it

            // If value is found.
            if (current->values[i] == value) {
                remove = true;
                do{
                    current->values[i]=current->values[i+1];
                    i++;
                }while(i<current->len);
                current->values[current->len]=0;
                listLen--;
                current->len--;

                // If the list is empty lets remove it
                if(current->len==0){
                    numChunks--;
                    if(current==head){
                        head = current->next;
                    }
                    if(current==tail){
                        tail = previous;
                    }
                    else{
                        previous->next=current->next;
                    }
                    delete current;

                }
            }
            i++;
        }
        previous = current;
        current = current->next;
    }

}

// Gets the length of the entire Chunklist.
template<class T>
int ChunkList<T>::GetLength() {

    int getLen = 0;                 // Set equal to 0
    Node* current = head;           // Point at the front.

    // Loop through chunks and count the lengths of each lisy
    for(int x = 0; x<numChunks; x++){
        getLen += current->len;

        // If there are more nodes
        if(current->next!=NULL) {
            current = current->next;
        }
    }

    // Update the listlen
    listLen = getLen;
    return getLen;
}

template<class T>
double ChunkList<T>::LoadFactor() {

    // Error Checking
    if(numChunks == 0) throw EmptyList();

    // Calculate and Return
    double  temp = ARRAY_SIZE*numChunks;
    double loadFactor = listLen/temp;
    return loadFactor;
}

template<class T>
bool ChunkList<T>::Contains(T value) {

    // Error handling
    if(head==NULL) throw EmptyList();

    // Point at head
    Node* current = head;

    while(current!=NULL) {

        // Error handling
        if(current->len==0) throw EmptyList();

        for (int i = 0; i <= current->len; i++) {
            if(current->values[i] == value){
                return true;
            }
        }
        current = current->next;
    }
    return false;
}

template<class T>
T ChunkList<T>::GetIndex(int i) {
    Node* current = head;

    // Error handling
    if(i>listLen)throw IndexOutOfBounds();
    if(i<0)throw IndexOutOfBounds();
    if(listLen==0)throw IndexOutOfBounds();

    // Variables for finding the index
    int loopsum = 0;
    int loopUpToPrev = 0;

    // Set = to first length
    loopsum = current->len;

    // Loops until loop is greater than or equal to i/the index we are looking for
    while(loopsum<=i&&current!=NULL){
        // Iterate to next Node
        current = current->next;

        // Book keep data
        loopUpToPrev = loopsum;
        loopsum+= current->len;

        // If last Node
        if(loopsum==i&&current->next!=NULL){
            current=current->next;
            return current->values[0];
        }
    }

    return current->values[i-loopUpToPrev];
}

template<class T>
void ChunkList<T>::ResetIterator() {
iterNode = head;                        // Iternode back to head
arrPos = 0;                             // Position back to 0
}

template<class T>
T ChunkList<T>::GetNextItem() {

    // Error handling
    if (iterNode->len <= 0) throw IteratorOutOfBounds();
    if (listLen <= 0) throw IteratorOutOfBounds();
    if (iterNode==NULL) throw IteratorOutOfBounds();

    //Check to see if we need to go to next node
    if (arrPos==iterNode->len){
        if (iterNode->next==NULL){              // Check if there is a next node
            throw IteratorOutOfBounds();
        }else {
            iterNode = iterNode->next;          // Else go to next node and set pos to 0
            arrPos = 0;
        }
    }
    float item = iterNode->values[arrPos];

    // Iterate
    arrPos++;
return item;
}

template<class T>
bool ChunkList<T>::IsEmpty() { //Checks to see if Chunklist is empty
    if(listLen == 0){
        return true;
    }
    return false;
}
