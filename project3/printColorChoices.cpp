#include <iostream>
using namespace std;

#include "printColorChoices.h"
#include "constants.h"

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains the definition of a global 
//function printColorChoices(). Since the program prints ColorChoices 
//in three situations, this function helps reduce duplicate code.

//This function prints out the guide for users to choose colors.
void printColorChoices()
{
    cout << INDEX_OF_RED << ". Red" << endl;
    cout << INDEX_OF_GREEN << ". Green" << endl;
    cout << INDEX_OF_BLUE << ". Blue" << endl;
    cout << INDEX_OF_BLACK << ". Black" << endl;
    cout << INDEX_OF_WHITE << ". White" << endl;
}