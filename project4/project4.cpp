#include <iostream>
using namespace std;

#include "SortedListClass.h"
#include "LIFOStackClass.h"
#include "FIFOQueueClass.h"

//Programmer: Xinyu Mei
//Date: Nov 9, 2023
//Purpose: This file contains the main function to test the data 
//structure classes.

//Do NOT remove any of the preprocessor directives in this file.
//They should not affect your ability to write test code in your
//main function below, and they must be in your submitted main
//file exactly as provided to you with the project.
#ifdef ANDREW_TEST
#include "andrewTest.h"
#else 

int main()
{
    //This is just a placeholder main function - it does exceptionally
    //little actual testing, so you'll want to add your own tests here.
    //Feel free to leave your tests in the version of this file you
    //submit, but we will not be running your main function, so the
    //output, etc., of your main doesn't need to match anything from
    //a sample output, etc.
    SortedListClass testList;
    int theVal;
    int outVal;
  
    cout << "Testing SortedListClass below:" << endl;
    testList.printForward();
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.insertValue(42);
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.insertValue(32);
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.insertValue(12);
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.insertValue(22);
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.printForward();
    testList.printBackward();
    testList.getElemAtIndex(2, outVal);
    cout << "The 3rd element is " << outVal << endl;
    

    SortedListClass copyList;
    copyList = SortedListClass(testList);
    cout << "num of elements: " << copyList.getNumElems() << endl;
    copyList.printForward();
    cout << "num of elements: " << copyList.getNumElems() << endl;
    copyList.printBackward();
    cout << "num of elements: " << copyList.getNumElems() << endl;
    copyList.getElemAtIndex(3, outVal);
    cout << "The 4th element is " << outVal << endl;

    testList.removeFront(theVal);
    cout << "deleted: " << theVal << endl;
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.printForward();
    testList.printBackward();
    testList.removeLast(theVal);
    cout << "deleted: " << theVal << endl;
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.printForward();
    testList.printBackward();
    testList.removeFront(theVal);
    cout << "deleted: " << theVal << endl;
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.printForward();
    testList.printBackward();
    testList.removeLast(theVal);
    cout << "deleted: " << theVal << endl;
    cout << "num of elements: " << testList.getNumElems() << endl;
    testList.printForward();
    testList.printBackward();
    copyList.printForward();
    copyList.printBackward();
    

    LIFOStackClass testStack;
    int outItem;

    cout << "Testing LIFOStackClass below:" << endl;
    testStack.print();
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.push(42);
    testStack.print();
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.push(32);
    testStack.print();
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.push(22);
    testStack.print();
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.push(12);
    testStack.print();
    testStack.pop(outItem);
    testStack.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.pop(outItem);
    testStack.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.pop(outItem);
    testStack.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testStack.getNumElems() << endl;
    testStack.pop(outItem);
    testStack.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testStack.getNumElems() << endl;

    FIFOQueueClass testQueue;

    cout << "Testing FIFOQueueClass below:" << endl;
    testQueue.print();
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.enqueue(42);
    testQueue.print();
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.enqueue(32);
    testQueue.print();
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.enqueue(22);
    testQueue.print();
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.enqueue(12);
    testQueue.print();
    testQueue.dequeue(outItem);
    testQueue.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.dequeue(outItem);
    testQueue.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.dequeue(outItem);
    testQueue.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testQueue.getNumElems() << endl;
    testQueue.dequeue(outItem);
    testQueue.print();
    cout << "deleted: " << outItem << endl;
    cout << "num of elems: " << testQueue.getNumElems() << endl;

    return 0;
}

#endif