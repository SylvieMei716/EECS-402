#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ColorImageClass.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "constants.h"

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains implementations of 
//all the ColorImageClass methods.

//This is construcor without any input parameters.
ColorImageClass::ColorImageClass() 
{
    numRows = IMAGE_SIZE_MIN;
    numCols = IMAGE_SIZE_MIN;
    imageArr = NULL;
}

//This is destructor for ColorImageClass.
ColorImageClass::~ColorImageClass() 
{
    for (int i = 0; i < numRows; i++) 
    {
        delete[] imageArr[i];
    }
    delete[] imageArr;
}


//If the input position is within valid range, this method sets the color at 
//the position to inColor and returns true; otherwise object is unchanged, and
//it returns false.
bool ColorImageClass::setColorAtLocation(
    RowColumnClass &inRowCol,
    ColorClass &inColor
    )
{
    if (inRowCol.getRow() >= IMAGE_SIZE_MIN &&
        inRowCol.getCol() >= IMAGE_SIZE_MIN && 
        inRowCol.getRow() <= numRows && 
        inRowCol.getCol() <= numCols)
    {
        imageArr[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
        return true;
    }
    else
    {
        return false;
    }
}

//If the input position is within valid range, this method assigns the 
//color at the position to inColor and returns true; otherwise object 
//is unchanged, and it returns false.
bool ColorImageClass::getColorAtLocation(
    RowColumnClass &inRowCol,
    ColorClass &outColor
    )
{
    if (inRowCol.getRow() >= IMAGE_SIZE_MIN &&
        inRowCol.getCol() >= IMAGE_SIZE_MIN && 
        inRowCol.getRow() <= numRows && 
        inRowCol.getCol() <= numCols)
    {
        outColor.setTo(imageArr[inRowCol.getRow()][inRowCol.getCol()]);
        return true;
    }
    else
    {
        return false;
    }
}

int ColorImageClass::getWidth()
{
    return numCols;
}

int ColorImageClass::getHeight()
{
    return numRows;
}

//This method takes in a file name and reads as a PPM file. 
//It checks whether the file is valid by checking the magic number "P3", 
//the height and width, and number of pixels.
bool ColorImageClass::readPPMFile(string filename)
{
    ifstream inFile;
    inFile.open(filename.c_str());
    
    if (!inFile) 
    {
        cout << "Error: Failed to open the image file." << endl;
        inFile.close();
        return false;
    }
    else
    {
        string magicNumber;
        int width, height, maxColorValue;
        inFile >> magicNumber >> width >> height >> maxColorValue;
        numRows = height;
        numCols = width;
        imageArr = new ColorClass*[numRows];
        for (int i = 0; i < numRows; i++) 
        {
            imageArr[i] = new ColorClass[numCols];
        }

        if (magicNumber != STANDARD_MAGIC_NUMBER)
        {
            cout << "Error: Invalid magic number - " 
                 << STANDARD_MAGIC_NUMBER << " is expected but found " 
                 << magicNumber << endl;
            inFile.close();
            return false;
        }

        else if (maxColorValue != MAX_COLOR_VALUE)
        {
            cout << "Error: Invalid max color value - " << MAX_COLOR_VALUE
                 << " is expected but found " << maxColorValue << endl;
            inFile.close();
            return false;
        }

        else if (width <= 0) 
        {
            cout << "Error: Invalid image dimensions - " 
                 << "Width should be > 0 but found " << width << endl;
            inFile.close();
            return false;
        }

        else if (height <= 0) 
        {
            cout << "Error: Invalid image dimensions - " 
                 << "Height should be > 0 but found " << height << endl;
            inFile.close();
            return false;
        }

        int pixelCount = 0;
        
        while (pixelCount < width * height) 
        {
            if (!imageArr[pixelCount / numCols]
                    [pixelCount % numCols].readColorFromFile(inFile))
            {
                cout << "Error: Invalid pixel data in the file. " 
                     << "Every color value should be an integer between "
                     << MIN_COLOR_VALUE << " and " << MAX_COLOR_VALUE 
                     << " but found pixel at"
                     << " row "<< pixelCount / width
                     << " column " << pixelCount % width << endl;
                inFile.close();
                return false;
            }
            pixelCount++;
        }

        inFile.close();

        if (pixelCount != width * height) 
        {
            cout << "Error: Number of pixels does not match "
                 << "image dimensions - " << width << "*" << height 
                 << " expected but found " << pixelCount << endl;
            inFile.close();
            return false;
        }
        
        return true;
    }
}

//This method annotates a rectangle on the image at some location user inputs.
void ColorImageClass::drawRectangle(
    RowColumnClass upperLeftCorner,
    RowColumnClass lowerRightCorner,
    ColorClass borderColor,
    bool ifFillRectangle
    )
{
    int startRow = upperLeftCorner.getRow();
    int startCol = upperLeftCorner.getCol();
    int endRow = lowerRightCorner.getRow();
    int endCol = lowerRightCorner.getCol();

    if (upperLeftCorner.getRow() > lowerRightCorner.getRow()) 
    {
        startRow = lowerRightCorner.getRow();
        endRow = upperLeftCorner.getRow();
        cout << "Wrong input detected. Automatically switched row value " 
             << "of upper left corner and lower right corner." << endl;
    }

    if (upperLeftCorner.getCol() > lowerRightCorner.getCol()) 
    {
        startCol = lowerRightCorner.getCol();
        endCol = upperLeftCorner.getCol();
        cout << "Wrong input detected. Automatically switched column value " 
             << "of upper left corner and lower right corner." << endl;
    }

    if (startRow < 0) 
    {
        startRow = 0;
        cout << "Row value of upper edge is out of bound. " 
             << "The program will draw only part of rectangle within bound." 
             << endl;
    }
    if (startCol < 0) 
    {
        startCol = 0;
        cout << "Column value of left edge is out of bound. " 
             << "The program will draw only part of rectangle within bound." 
             << endl;
    }
    if (endRow >= numRows) 
    {
        endRow = numRows - 1;
        cout << "Row value of lower edge is out of bound. " 
             << "The program will draw only part of rectangle within bound." 
             << endl;
    }
    if (endCol >= numCols) 
    {
        endCol = numCols - 1;
        cout << "Row value of right edge is out of bound. " 
             << "The program will draw only part of rectangle within bound." 
             << endl;
    }

    if (ifFillRectangle) 
    {
        for (int i = startRow; i <= endRow; i++) 
        {
            for (int j = startCol; j <= endCol; j++) 
            {
                RowColumnClass tempPixel = RowColumnClass(i,j);
                setColorAtLocation(tempPixel, borderColor);
            }
        }
    } 
    else 
    {
        for (int i = startRow; i <= endRow; i++) 
        {
            if (i == startRow || i == endRow) 
            {
                for (int j = startCol; j <= endCol; j++) 
                {
                    RowColumnClass tempPixel = RowColumnClass(i,j);
                    setColorAtLocation(tempPixel, borderColor);
                }
            } 
            else 
            {
                RowColumnClass tempPixel = RowColumnClass(i, startCol);
                setColorAtLocation(tempPixel, borderColor);
                tempPixel = RowColumnClass(i,endCol);
                setColorAtLocation(tempPixel, borderColor);
            }
        }
    }
}

//This method write out object as a PPM file.
bool ColorImageClass::writePPMFile(string filename) 
{
    ofstream outFile;
    outFile.open(filename.c_str());

    if (!outFile) 
    {
        cout << "Error: Failed to open the output image file." << endl;
        return false;
    }

    outFile << "P3" << endl;
    outFile << numCols << " " << numRows - 1 << endl;
    outFile << MAX_COLOR_VALUE << endl;

    for (int i = 0; i < numRows - 1; i++) 
    {
        for (int j = 0; j < numCols; j++) 
        {
            imageArr[i][j].printComponentValues(outFile); 
        }
        outFile << endl;
    }

    outFile.close();
    return true;
}

//This method annotates a pattern given by user to 
//the image at a location given by user and changes it to some color.
bool ColorImageClass::drawPattern(
    string filename, 
    RowColumnClass upperLeftCorner, 
    ColorClass patternColor)
{
    ifstream inFile;
    inFile.open(filename.c_str());
    if (!inFile) 
    {
        cout << "Error: Failed to open the image file." << endl;
        inFile.close();
        return false;
    }

    int width, height;
    inFile >> width >> height;

    if (width <= 0) 
    {
        cout << "Error: Invalid pattern dimensions - " 
             << "Width should be > 0 but found " << width << endl;
        inFile.close();
        return false;
    }

    else if (height <= 0) 
    {
        cout << "Error: Invalid pattern dimensions - " 
             << "Height should be > 0 but found " << height << endl;
        inFile.close();
        return false;
    }

    int pixelCount = 0;
    int ifFillPixel;
    while (!inFile.eof()) 
    {
        inFile >> ifFillPixel;
        if (!(ifFillPixel == 0 || ifFillPixel == 1))
        {
            cout << "Error: Invalid pixel data in the file. " 
                 << "Every pixel should be an integer showing "
                 << "whether to fill color or not, but found" 
                 << " row "<< pixelCount / width
                 << " column " << pixelCount % width << endl;
            inFile.close();
            return false;
        }
        else if (ifFillPixel)
        {
            imageArr[upperLeftCorner.getRow() + 
                     pixelCount / width]
                    [upperLeftCorner.getCol() + 
                     pixelCount % width].setTo(patternColor);
        }
        pixelCount++;
    }

    inFile.close();

    if (pixelCount - 1 != width * height) 
    {
        cout << "Error: Number of pixels does not match "
             << "image dimensions - " << width * height 
             << " expected but found " << pixelCount - 1 << endl;
        inFile.close();
        return false;
    }
    else
    {
        return true;
    }
}

//This method inserts an image given by user to 
//the object image at a location given by user, 
//but ignoring the pixels with transparency color.
bool ColorImageClass::insertImage(
    ColorImageClass imageToInsert, 
    RowColumnClass upperLeftCorner, 
    ColorClass transparencyColor)
{
    int startRow = upperLeftCorner.getRow();
    int startCol = upperLeftCorner.getCol();
    int endRow = startRow + imageToInsert.getHeight();
    int endCol = startCol + imageToInsert.getWidth();

    if (startRow < 0) 
    {
        startRow = 0;
        cout << "Row value of the image's upper edge is out of bound. " 
             << "The program will draw only part of image within bound." 
             << endl;
    }
    if (startCol < 0) 
    {
        startCol = 0;
        cout << "Column value of the image's left edge is out of bound. " 
             << "The program will draw only part of image within bound." 
             << endl;
    }
    if (endRow >= numRows) 
    {
        endRow = numRows - 1;
        cout << "Row value of the image's lower edge is out of bound. " 
             << "The program will draw only part of image within bound." 
             << endl;
    }
    if (endCol >= numCols) 
    {
        endCol = numCols - 1;
        cout << "Column value of the image's right edge is out of bound. " 
             << "The program will draw only part of image within bound." 
             << endl;
    }
    
    for (int i = startRow; i < endRow; i++) 
    {
        for (int j = startCol; j < endCol; j++) 
        {
            RowColumnClass tempLocation = 
            RowColumnClass(i - startRow, j - startCol);

            ColorClass pixelColor;
            imageToInsert.getColorAtLocation(tempLocation, pixelColor);

            if (!pixelColor.isTheSameColor(transparencyColor)) 
            {
                RowColumnClass tempPixel = RowColumnClass(i, j);
                setColorAtLocation(tempPixel, pixelColor);
            }
        }
    }
        return true;
}
