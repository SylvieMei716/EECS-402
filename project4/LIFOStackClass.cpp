#include <iostream>
using namespace std;

#include "LIFOStackClass.h"

//Programmer: Xinyu Mei
//Date: Nov 9, 2023
//Purpose: This file contains implementations of all the 
//LIFOStackClass methods.

//Default Constructor. Will properly initialize a stack to 
//be an empty stack, to which values can be added.
LIFOStackClass::LIFOStackClass()
{
    head = NULL;
    tail = NULL;
}

//NOTE: This class does NOT have a copy ctor or an overload
//      assignment operator - therefore, using either of those 
//      things will result in a shallow copy. Users should not
//      attempt to copy a LIFOStackClass object using either of 
//      these approaches!

//Destructor. Responsible for making sure any dynamic memory 
//associated with a object is freed up when the object is 
//being destroyed.
LIFOStackClass::~LIFOStackClass()
{
    clear();
}

//Inserts the value provided (newItem) into the stack.
void LIFOStackClass::push(const int &newItem)
{
    

    if (head == NULL)
    {
        LinkedNodeClass *newNode;
        newNode = new LinkedNodeClass(NULL, newItem, NULL);
        head = newNode;
        tail = newNode;
    }
    else
    {
        LinkedNodeClass *newNode;
        newNode = new LinkedNodeClass(NULL, newItem, head);
        head = newNode;
        newNode->setBeforeAndAfterPointers();
    }
}

//Attempts to take the next item out of the stack. If the
//stack is empty, the function returns false and the state
//of the reference parameter (outItem) is undefined. If the
//stack is not empty, the function returns true and outItem
//becomes a copy of the next item in the stack, which is
//removed from the data structure.
bool LIFOStackClass::pop(int &outItem)
{
    if (head == NULL)
    {
        return false;
    }
    else
    {
        outItem = head->getValue();
        LinkedNodeClass *temp = head;

        if (head == tail)
        {
            head = NULL;
            tail = NULL;
        }
        else
        {
            head = head->getNext();
            head->setBeforeAndAfterPointers();
        }
        delete temp;
        return true;
    }
}

//Prints out the contents of the stack. All printing is done
//on one line, using a single space to separate values, and a 
//single newline character is printed at the end. Values will
//be printed such that the next value that would be popped
//is printed first.
void LIFOStackClass::print() const
{
    LinkedNodeClass *nodePtr = head;

    while (nodePtr != NULL)
    {
        cout << nodePtr->getValue() << " ";
        nodePtr = nodePtr->getNext();
    }
    cout << endl;
}

//Return the number of nodes contained in the stack.
int LIFOStackClass::getNumElems() const
{
    int numElemsCount = 0;
    LinkedNodeClass *nodePtr = head;

    while (nodePtr != NULL)
    {
        numElemsCount++;
        nodePtr = nodePtr->getNext();
    }

    return numElemsCount;
}

//Clears the stack to an empty state without resulting in any
//memory leaks.
void LIFOStackClass::clear()
{
    while (head != NULL)
    {
        LinkedNodeClass *temp = head;
        head = head->getNext();
        delete temp;
    }
    tail = NULL;
}