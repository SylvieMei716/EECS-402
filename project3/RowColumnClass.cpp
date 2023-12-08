#include <iostream>
using namespace std;

#include "RowColumnClass.h"
#include "constants.h"

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains implementations of 
//all the RowColumnClass methods.

//This method defaultly sets object to position[-99999,-99999].
RowColumnClass::RowColumnClass()
{
    rowValue = INITIAL_ROW;
    colValue = INITIAL_COL;
}

//This method initializes object according to input row / column value.
RowColumnClass::RowColumnClass(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

//This method set sthe position of pixel to input row / column value.
void RowColumnClass::setRowCol(int inRow, int inCol)
{
    rowValue = inRow;
    colValue = inCol;
}

//This method returns row value of object.
int RowColumnClass::getRow()
{
    return rowValue;
}

//This method returns column value of object.
int RowColumnClass::getCol()
{
    return colValue;
}
