#include <iostream>
using namespace std;

#include "FIFOQueueClass.h"

//Programmer: Xinyu Mei
//Date: Nov 28, 2023
//Purpose: This file contains implementations of all the 
//FIFOQueueClass methods.

//Default Constructor. Will properly initialize a queue to
//be an empty queue, to which values can be added.
template < class T >
FIFOQueueClass< T >::FIFOQueueClass()
{
  head = NULL;
  tail = NULL;
}

//NOTE: This class does NOT have a copy ctor or an overload
//  assignment operator - therefore, using either of those
//  things will result in a shallow copy. Users should not
//  attempt to copy a FIFOQueueClass object using either of
//  these approaches!

//Destructor. Responsible for making sure any dynamic memory
//associated with an object is freed up when the object is 
//being destroyed.
template < class T >
FIFOQueueClass< T >::~FIFOQueueClass()
{
  clear();
}

//Inserts the value provided (newItem) into the queue.
template < class T >
void FIFOQueueClass< T >::enqueue(const T &newItem)
{
  if (tail == NULL)
  {
    LinkedNodeClass< T > *newNode;
    newNode = new LinkedNodeClass< T >(NULL, newItem, NULL);
    head = newNode;
    tail = newNode;
  }
  else
  {
    LinkedNodeClass< T > *newNode;
    newNode = new LinkedNodeClass< T >(tail, newItem, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
}

//Attempts to take the next item out of the queue. If the
//queue is empty, the function returns false and the state 
//of the reference parameter (outItem) is undefined. If the
//queue is not empty, the function returns true and outItem
//becomes a copy of the next item in the queue, which is 
//removed from the data structure.
template < class T >
bool FIFOQueueClass< T >::dequeue(T &outItem)
{
  if (head == NULL)
  {
    return false;
  }
  else
  {
    outItem = head->getValue();
    LinkedNodeClass< T > *temp = head;

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

//Prints out the contents of the queue. All printing is done 
//on one line, using a single space to separate values, and a 
//single newline character is printed at the end. Values will
//be printed such that the next value that would be dequeued
//is printed first.
template < class T >
void FIFOQueueClass< T >::print() const
{
  LinkedNodeClass< T > *nodePtr;
  nodePtr = head;

  while (nodePtr != NULL)
  {
    cout << nodePtr->getValue() << " ";
    nodePtr = nodePtr->getNext();
  }
  cout << endl;
}

//Returns the number of nodes contained in the queue.
template < class T >
int FIFOQueueClass< T >::getNumElems() const
{
  int numElemsCount = 0;
  LinkedNodeClass< T > *nodePtr;
  nodePtr = head;

  while (nodePtr != NULL)
  {
    numElemsCount++;
    nodePtr = nodePtr->getNext();
  }

  return numElemsCount;
}

//Clears the queue to an empty state without resulting in any
//memory leaks.
template < class T >
void FIFOQueueClass< T >::clear()
{
  while (head != NULL)
  {
    LinkedNodeClass< T > *temp = head;
    head = head->getNext();
    delete temp;
  }
  tail = NULL;
}