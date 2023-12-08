#include <iostream>
using namespace std;

#include "SortedListClass.h"
#include "LinkedNodeClass.h"

//Programmer: Xinyu Mei
//Date: Nov 28, 2023
//Purpose: This file contains implementations of all the 
//SortedListClass methods.

//Default Constructor. Will properly initialize a list to 
//be an empty list, to which values can be added.
template < class T >
SortedListClass< T >::SortedListClass()
{
  head = NULL;
  tail = NULL;
}

//Copy constructor. Will make a complete (deep) copy of the list, such
//that one can be changed without affecting the other.
template < class T >
SortedListClass< T >::SortedListClass(const SortedListClass< T > &rhs)
{
  head = NULL;
  tail = NULL;

  LinkedNodeClass< T > *originalPtr = rhs.head;
  LinkedNodeClass< T > *lastNode = NULL;

  while (originalPtr != NULL) 
  {
    LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >(lastNode, 
    originalPtr->getValue(), NULL);

    if (lastNode == NULL) 
    {
      head = newNode;
    } 
    else 
    {
      newNode->setBeforeAndAfterPointers();
    }

    lastNode = newNode;
    originalPtr = originalPtr->getNext();
  }

  tail = lastNode;
}

//Destructor. Responsible for makeing sure any dynamic memory
//associated with an object is freed up when the object is 
//being destroyed.
template < class T >
SortedListClass< T >::~SortedListClass()
{
  clear();
}

//Assignmeng operator. Will assign one list (on left hand side of
//operator) to be a duplicate of the other (on the right hand side
//of operator).
template < class T >
SortedListClass< T >& SortedListClass< T >::operator=(
  const SortedListClass &rhs)
{
  clear(); // Clear existing data

  LinkedNodeClass< T > *originalPtr = rhs.head;
  LinkedNodeClass< T > *lastNode = NULL;

  while (originalPtr != NULL) 
  {
    LinkedNodeClass< T > *newNode = new LinkedNodeClass< T >(lastNode, 
    originalPtr->getValue(), NULL);

    if (lastNode == NULL) 
    {
      head = newNode;
    } 
    else 
    {
      newNode->setBeforeAndAfterPointers();
    }

    lastNode = newNode;
    originalPtr = originalPtr->getNext();
  }

  tail = lastNode;

  return *this;
}

//Clears the list to an empty state without resulting in any
//memory leaks.
template < class T >
void SortedListClass< T >::clear()
{
  LinkedNodeClass< T > *nodePtr;
  nodePtr = head;
  while (nodePtr != NULL) 
  {
    LinkedNodeClass< T > *nextNode = nodePtr->getNext();
    delete nodePtr;
    nodePtr = nextNode;
  }

  head = NULL;
  tail = NULL;
}

//Allows the user to insert a value into the list. Since this
//is a sorted list, there is no need to specify where in the list
//to insert the element. It will insert it in the appropriate
//location based on the value being inserted. If the node value
//being inserted is found to be "equal to" one or more node values
//already in the list, the newly inserted node will be placed AFTER
//the previously inserted nodes.
//Input parameter is the value to insert into the list.
template < class T >
void SortedListClass< T >::insertValue(const T &valToInsert)
{
  if (head == NULL) //empty list, head and tail point to newNode
  {
    LinkedNodeClass< T > *newNode;
    newNode = new LinkedNodeClass< T >(NULL, valToInsert, NULL);
    head = newNode;
    tail = newNode;
  }
  else if (valToInsert < head->getValue()) //insert in the front
  {
    LinkedNodeClass< T > *newNode;
    newNode = new LinkedNodeClass< T >(NULL, valToInsert, head);
    newNode->setBeforeAndAfterPointers();
    head = newNode;
  }
  else if (!(valToInsert < tail->getValue())) //insert from the back
  {
    LinkedNodeClass< T > *newNode;
    newNode = new LinkedNodeClass< T >(tail, valToInsert, NULL);
    newNode->setBeforeAndAfterPointers();
    tail = newNode;
  }
  else //insert in the middle
  {
    LinkedNodeClass< T > *nodePtr = head;
    while (nodePtr != NULL)
    {
      if (!(valToInsert < nodePtr->getValue()))
      {
      nodePtr = nodePtr->getNext();
      }
      else
      {
      LinkedNodeClass< T > *prev;
      prev = nodePtr->getPrev();
      LinkedNodeClass< T > *newNode;
      newNode = new LinkedNodeClass< T >(prev, valToInsert, nodePtr);
      newNode->setBeforeAndAfterPointers();
      nodePtr = NULL;
      }
    }
  }
}

//Prints the contents of the list from head to tail to the screen.
//Begins with a line reading "Forward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End of List Contents" to indicate the end of the list.
template < class T >
void SortedListClass< T >::printForward() const
{
  LinkedNodeClass< T > *nodePtr;
  nodePtr = head;

  cout << "Forward List Contents Follow:" << endl;
  while (nodePtr != NULL)
  {
    cout << "  " << nodePtr->getValue() << endl;

    nodePtr = nodePtr->getNext();
  }
  cout << "End of List Contents" << endl;
}

//Prints the contents of the list from tail to head to the screen.
//Begins with a line reading "Backward List Contents Follow:", then
//prints one list element per line, indented two spaces, then prints
//the line "End of List Contents" to indicate the end of the list.
template < class T >
void SortedListClass< T >::printBackward() const
{
  LinkedNodeClass< T > *nodePtr;
  nodePtr = tail;

  cout << "Backward List Contents Follow:" << endl;
  while (nodePtr != NULL)
  {
    cout << "  " << nodePtr->getValue() << endl;

    nodePtr = nodePtr->getPrev();
  }
  cout << "End of List Contents" << endl;
}

//Removes the front item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the first item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template < class T >
bool SortedListClass< T >::removeFront(T &theVal)
{
  bool didDeleteItem;

  if (head == NULL)
  {
    didDeleteItem = false;
  }
  else
  {
    theVal = head->getValue();
    
    if (head == tail)
    {
      delete head;
      head = NULL;
      tail = NULL;
    }
    else
    {
      LinkedNodeClass< T > *newHeadPtr;
      newHeadPtr = head->getNext();
      newHeadPtr->setPreviousPointerToNULL();
      delete head;
      head = newHeadPtr; 
    }
    
    didDeleteItem =  true;
  }

  return didDeleteItem;
}

//Removes the last item from the list and returns the value that
//was contained in it via the reference parameter. If the list
//was empty, the function returns false to indicate failure, and
//the contents of the reference parameter upon return is undefined.
//If the list was not empty and the last item was successfully
//removed, true is returned, and the reference parameter will
//be set to the item that was removed.
template < class T >
bool SortedListClass< T >::removeLast(T &theVal)
{
  bool didDeleteItem;

  if (tail == NULL)
  {
    didDeleteItem = false;
  }
  else
  {
    theVal = tail->getValue();

    if (head == tail)
    {
      delete tail;
      head = NULL;
      tail = NULL;
    }
    else
    {
    LinkedNodeClass< T > *newTailPtr;
    newTailPtr = tail->getPrev();
    newTailPtr->setNextPointerToNULL();
    delete tail;
    tail = newTailPtr;
  }
  didDeleteItem = true;
  }

  return didDeleteItem;
}

//Returns the number of nodes contained in the list.
template < class T >
int SortedListClass< T >::getNumElems() const
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

//Provides the value stored in the node at index provided in the
//0-based "index" parameter. If the index is out of range, then outVal
//remains unchanged and false is returned. Otherwise, the function
//returns true, and the reference parameter outVal will contain 
//a copy of the value at that location.
template < class T >
bool SortedListClass< T >::getElemAtIndex(const int index, T &outVal) const
{
  LinkedNodeClass< T > *nodePtr;
  nodePtr = head;

  if(index >= getNumElems())
  {
    return false;
  }
  else
  {
    for (int i = 0; i < index; i++)
    {
      nodePtr = nodePtr->getNext();
    }
    outVal = nodePtr->getValue();
    return true;
  }
}