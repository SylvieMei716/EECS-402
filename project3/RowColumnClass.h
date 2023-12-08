#ifndef _ROWCOLUMNCLASS_H_
#define _ROWCOLUMNCLASS_H_

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains definitions of 
//all the RowColumnClass methods.

class RowColumnClass
{
    private:
        //Attributes of object: row & column value, showing the position of pixel
        int rowValue;
        int colValue;

    public:
        //Set initial value of a color object's RGB value, with & without input
        RowColumnClass();
        RowColumnClass(int inRow, int inCol);

        //Set the position of pixel according to input row value / column value
        void setRowCol(int inRow, int inCol);

        //Return row value / column value of object
        int getRow();
        int getCol();

};

#endif //_ROWCOLUMNCLASS_H_