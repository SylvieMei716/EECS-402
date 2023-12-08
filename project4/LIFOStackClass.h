#ifndef _LIFOSTACKCLASS_H_
#define _LIFOSTACKCLASS_H_

#include "LinkedNodeClass.h"

//Programmer: Xinyu Mei
//Date: Nov 9, 2023
//Purpose: This file contains definitions of all the LIFOStackClass
//attributes and methods.

class LIFOStackClass 
{
    private:
        LinkedNodeClass *head; //Points to the first node in a stack, or NULL
                               //if stack is empty.
        LinkedNodeClass *tail; //Points to the last node in a stack, or NULL
                               //if stack is empty.
    
    public:
        //Default Constructor. Will properly initialize a stack to 
        //be an empty stack, to which values can be added.
        LIFOStackClass();

        //NOTE: This class does NOT have a copy ctor or an overload
        //      assignment operator - therefore, using either of those 
        //      things will result in a shallow copy. Users should not
        //      attempt to copy a LIFOStackClass object using either of 
        //      these approaches!

        //Destructor. Responsible for making sure any dynamic memory 
        //associated with a object is freed up when the object is 
        //being destroyed.
        ~LIFOStackClass();

        //Inserts the value provided (newItem) into the stack.
        void push(const int &newItem);

        //Attempts to take the next item out of the stack. If the
        //stack is empty, the function returns false and the state
        //of the reference parameter (outItem) is undefined. If the
        //stack is not empty, the function returns true and outItem
        //becomes a copy of the next item in the stack, which is
        //removed from the data structure.
        bool pop(int &outItem);

        //Prints out the contents of the stack. All printing is done
        //on one line, using a single space to separate values, and a 
        //single newline character is printed at the end. Values will
        //be printed such that the next value that would be popped
        //is printed first.
        void print() const;

        //Return the number of nodes contained in the stack.
        int getNumElems() const;

        //Clears the stack to an empty state without resulting in any
        //memory leaks.
        void clear();
};

#endif