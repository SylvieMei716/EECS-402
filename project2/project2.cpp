#include <iostream>
using namespace std;

//Programmer: Xinyu Mei
//Date: September 26, 2023
//EECS 402 Project 2
//Purpose: This programme is to develop some simple classes to 
//represent and utilize colors and images.

const int MAX_COLOR_VALUE = 1000;
const int MIN_COLOR_VALUE = 0;
const int IMAGE_SIZE_DIM0 = 10;
const int IMAGE_SIZE_DIM1 = 18;
const int INITIAL_ROW = -99999;
const int INITIAL_COL = -99999;
const int IMAGE_SIZE_MIN = 0;

//To judge whether a color object's RGB values are within valid range
bool wasClipped(int &inRed, int &inGreen, int &inBlue);

class ColorClass
{
  public:
    //Set initial value of a color object's RGB value, with & without input
    ColorClass();
    ColorClass(int inRed, int inGreen, int inBlue);

    //Set the color's component color values to form the color indicated
    void setToBlack();
    void setToRed();
    void setToGreen();
    void setToBlue();
    void setToWhite();

    //Set the color object's RGB values to provided values
    bool setTo(int inRed, int inGreen, int inBlue);
    bool setTo(ColorClass &inColor);

    //Add or subtract to color object's RGB values according to rhs object
    bool addColor(ColorClass &rhs);
    bool subtractColor(ColorClass &rhs);

    //Adjust the color object's brightness according to the adjFactor
    //object turns brighter if adjFactor > 1, dimmer if adjFactor < 1
    bool adjustBrightness(double adjFactor);

    //Print the component color values to the console
    void printComponentValues();

  private:
    //Attributes of the object: RGB value
    int redValue;
    int greenValue;
    int blueValue;

};

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
    void setRow(int inRow);
    void setCol(int inCol);

    //Return row value / column value of object
    int getRow();
    int getCol();

    //Add the row and column index values in parameter to object
    void addRowColTo(RowColumnClass &inRowCol);

    //Print object's position value in the format "[<row>,<col>]"
    void printRowCol();

};

class ColorImageClass
{

  public:
    //Defaultly set all pixels in the image to full black
    ColorImageClass();

    //Initialize all image pixels to inColor
    void initializeTo(ColorClass &inColor);

    //Add rhsImg to object
    bool addImageTo(ColorImageClass &rhsImg);

    //Add up all input images, then assign the sum to object
    bool addImages(int numImgsToAdd, 
         ColorImageClass imagesToAdd []
         );

    //Set color at position provided by inRowCol to inColor
    bool setColorAtLocation(
         RowColumnClass &inRowCol,
         ColorClass &inColor
         );

    //Turns the parameter outColor into color at position provided by inRowCol
    bool getColorAtLocation(
         RowColumnClass &inRowCol,
         ColorClass &outColor
         );

    //Print the contents of the image to the screen
    void printImage();

  private:
    //Attribute of objecg: a 2D array of ColorClass objects
    ColorClass image[IMAGE_SIZE_DIM0][IMAGE_SIZE_DIM1];

};

#ifdef ANDREW_TEST
#include "andrewTest.h"
#else

int main()
{
    ColorClass testColor;
    ColorClass testRhsColor;
    RowColumnClass testRowCol;
    RowColumnClass testRowColOther(111, 222);
    ColorImageClass testImage;
    ColorImageClass testImages[3];

    //Test some basic ColorClass operations...
    cout << "Initial: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToBlack();
    cout << "Black: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setToGreen();
    cout << "Green: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.adjustBrightness(0.5);
    cout << "Dimmer Green: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setTo(11, 111, 1111);
    cout << "Color: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.addColor(testRhsColor);
    cout << "Added Color: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.subtractColor(testRhsColor);
    cout << "Subtracted Color: ";
    testColor.printComponentValues();
    cout << endl;

    testColor.setTo(testRhsColor);
    cout << "Final Color: ";
    testColor.printComponentValues();
    cout << endl;

    //Test some basic RowColumnClass operations...
    cout << "Want defaults: ";
    testRowCol.printRowCol();
    cout << endl;

    testRowCol.setRowCol(2, 8);
    cout << "Want 2,8: ";
    testRowCol.printRowCol();
    cout << endl;

    cout << "Want 111, 222: ";
    testRowColOther.printRowCol();
    cout << endl;

    testRowColOther.setRowCol(4, 2);
    testRowCol.addRowColTo(testRowColOther);
    cout << "Want 6,10: ";
    testRowCol.printRowCol();
    cout << endl;

    //Test some basic ColorImageClass operations...
    testColor.setToRed();
    testImage.initializeTo(testColor);

    testRowCol.setRowCol(555, 5);
    cout << "Want: Color at [555,5]: Invalid Index!" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;

    testRowCol.setRow(4);
    cout << "Want: Color at [4,5]: R: 1000 G: 0 B: 0" << endl;
    cout << "Color at ";
    testRowCol.printRowCol();
    cout << ": ";
    if (testImage.getColorAtLocation(testRowCol, testColor))
    {
      testColor.printComponentValues();
    }
    else
    {
      cout << "Invalid Index!";
    }
    cout << endl;

    //Set up an array of images of different colors
    testColor.setToRed();
    testColor.adjustBrightness(0.25);
    testImages[0].initializeTo(testColor);
    testColor.setToBlue();
    testColor.adjustBrightness(0.75);
    testImages[1].initializeTo(testColor);
    testColor.setToGreen();
    testImages[2].initializeTo(testColor);

    //Modify a few individual pixel colors
    testRowCol.setRowCol(4, 2);
    testColor.setToWhite();
    testImages[1].setColorAtLocation(testRowCol, testColor);

    testRowCol.setRowCol(2, 4);
    testColor.setToBlack();
    testImages[2].setColorAtLocation(testRowCol, testColor);

    //Add up all images in testImages array and assign result
    //to the testImage image
    testImage.addImages(3, testImages);
  
    //Check some certain values
    cout << "Added values:" << endl;
    for (int colInd = 0; colInd < 8; colInd += 2)
    {
      testRowCol.setRowCol(4, colInd);
      cout << "Color at ";
      testRowCol.printRowCol();
      cout << ": ";
      if (testImage.getColorAtLocation(testRowCol, testColor))
      {
        testColor.printComponentValues();
      }
      else
      {
        cout << "Invalid Index!";
      }
      cout << endl;
    }
  
    for (int rowInd = 0; rowInd < 8; rowInd += 2)
    {
      testRowCol.setRowCol(rowInd, 4);
      cout << "Color at ";
      testRowCol.printRowCol();
      cout << ": ";
      if (testImage.getColorAtLocation(testRowCol, testColor))
      {
        testColor.printComponentValues();
      }
      else
      {
        cout << "Invalid Index!";
      }
      cout << endl;
    }
  
    cout << "Printing entire test image:" << endl;
    testImage.printImage();

    return 0;
}

#endif

//This method defaultly sets the color object to full white
ColorClass::ColorClass()
{
    redValue = MAX_COLOR_VALUE;
    greenValue = MAX_COLOR_VALUE;
    blueValue = MAX_COLOR_VALUE;
}

//This method initials the color object according to input attribute value
ColorClass::ColorClass(int inRed, int inGreen, int inBlue)
{
    redValue = inRed;
    greenValue = inGreen;
    blueValue = inBlue;
}

//This method sets the color object to full black
void ColorClass::setToBlack()
{
    setTo(MIN_COLOR_VALUE, MIN_COLOR_VALUE, MIN_COLOR_VALUE);
}

//This method sets the color object to full red
void ColorClass::setToRed()
{
    setTo(MAX_COLOR_VALUE, MIN_COLOR_VALUE, MIN_COLOR_VALUE);
}

//This method sets the color object to full green
void ColorClass::setToGreen()
{
    setTo(MIN_COLOR_VALUE, MAX_COLOR_VALUE, MIN_COLOR_VALUE);
}

//This method sets the color object to full blue
void ColorClass::setToBlue()
{
    setTo(MIN_COLOR_VALUE, MIN_COLOR_VALUE, MAX_COLOR_VALUE);
}

//This method sets the color object to full white
void ColorClass::setToWhite()
{
    setTo(MAX_COLOR_VALUE, MAX_COLOR_VALUE, MAX_COLOR_VALUE);
}

//This method sets the color object according to input attribute values.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass::setTo(int inRed, int inGreen, int inBlue)
{
    redValue = inRed;
    greenValue = inGreen;
    blueValue = inBlue;
    return wasClipped(redValue, greenValue, blueValue);
}

//This method sets the color object according to input ColorClass object.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass::setTo(ColorClass &inColor)
{
    return setTo(inColor.redValue, inColor.greenValue, inColor.blueValue);
}

//This method adds input ColorClass object to the color object.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass::addColor(ColorClass &rhs)
{
    redValue += rhs.redValue;
    greenValue += rhs.greenValue;
    blueValue += rhs.blueValue;
    return setTo(redValue, greenValue, blueValue);
}

//This method subtracts input ColorClass object to the color object.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass::subtractColor(ColorClass &rhs)
{
    redValue -= rhs.redValue;
    greenValue -= rhs.greenValue;
    blueValue -= rhs.blueValue;
    return setTo(redValue, greenValue, blueValue);
}

//This method adjusts the color object's brightness according to input factor.
//If adjFactor > 1, the object turns brighter, otherwise it turns dimmer.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass:: adjustBrightness(double adjFactor)
{
    redValue *= adjFactor;
    greenValue *= adjFactor;
    blueValue *= adjFactor;
    return setTo(redValue, greenValue, blueValue);
}

//This method prints the component color values to the console.
void ColorClass::printComponentValues()
{
    cout << "R: " << redValue << " G: " << 
    greenValue << " B: " << blueValue;
}

//This method judges whether color object's RGB values are within valid range.
//If not within valid range, "clipping" is needed and processed.
//If "clipping" is needed, it returns true; otherwise it returns false.
bool wasClipped(int &inRed, int &inGreen, int &inBlue)
{
    if (
        inRed >= MIN_COLOR_VALUE && inRed <= MAX_COLOR_VALUE && 
        inGreen >= MIN_COLOR_VALUE && inGreen <= MAX_COLOR_VALUE && 
        inBlue >= MIN_COLOR_VALUE && inBlue <= MAX_COLOR_VALUE
    )
    {
        return false;
    }
    else
    {
        if (inRed < MIN_COLOR_VALUE)
        {
            inRed = MIN_COLOR_VALUE;
        }
        if (inRed > MAX_COLOR_VALUE)
        {
            inRed = MAX_COLOR_VALUE;
        }
        if (inGreen < MIN_COLOR_VALUE)
        {
            inGreen = MIN_COLOR_VALUE;
        }
        if (inGreen > MAX_COLOR_VALUE)
        {
            inGreen = MAX_COLOR_VALUE;
        }
        if (inBlue < MIN_COLOR_VALUE)
        {
            inBlue = MIN_COLOR_VALUE;
        }
        if (inBlue > MAX_COLOR_VALUE)
        {
            inBlue = MAX_COLOR_VALUE;
        }
        return true;
    }
}

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

//This method set sthe position of pixel according to input row value.
void RowColumnClass::setRow(int inRow)
{
    rowValue = inRow;
}

//This method set sthe position of pixel according to input column value.
void RowColumnClass::setCol(int inCol)
{
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

//This method adds the row and column index values in parameter to object.
void RowColumnClass::addRowColTo(RowColumnClass &inRowCol)
{
    rowValue += inRowCol.rowValue;
    colValue += inRowCol.colValue;
}

//This method prints object's position value in the format "[<row>,<col>]".
void RowColumnClass::printRowCol()
{
    cout << "[" << RowColumnClass::getRow() 
         << "," << RowColumnClass::getCol() << "]";
}

//This method defaultly sets object to an image full of fullblack pixels.
ColorImageClass::ColorImageClass()
{
    int cntRow;
    int cntCol;

    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            image[cntRow][cntCol].setToBlack();
        }
    }
}

//This method defaultly initializes object to an image full of inColor pixels.
void ColorImageClass::initializeTo(ColorClass &inColor)
{
    int cntRow;
    int cntCol;

    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            image[cntRow][cntCol].setTo(inColor);
        }
    }
}

//This method adds rhsImg to object.
//If "clipping" was needed, it returns true; otherwise, it returns false.
bool ColorImageClass::addImageTo(ColorImageClass &rhsImg)
{
    int cntRow;
    int cntCol;
    int flag = 0;

    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            if (image[cntRow][cntCol].addColor(rhsImg.image[cntRow][cntCol]))
            {
                flag = 1;
            }
            
        }
    }
    if (flag == 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This method assigns the some of all input images to object.
//If "clipping" was needed, it returns true; otherwise, it returns false.
bool ColorImageClass::addImages(
    int numImgsToAdd,
    ColorImageClass imagesToAdd []
    )
{
    int cntImgsToAdd;
    int cntRow;
    int cntCol;
    ColorImageClass initialImgToAdd;

    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            image[cntRow][cntCol].setToBlack();
        }
    }
    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            initialImgToAdd.image[cntRow][cntCol].setToBlack();
        } 
    }
    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
    	for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1; cntCol++)
        {
            for (cntImgsToAdd = 0; cntImgsToAdd < numImgsToAdd; cntImgsToAdd++)
            {
                image[cntRow][cntCol].addColor(
                    imagesToAdd[cntImgsToAdd].image[cntRow][cntCol]);
            }
        } 
	}
    if (this->addImageTo(initialImgToAdd))
    {
        return true;
    }
    else
    {
        return false;
    }
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
        inRowCol.getRow() <= IMAGE_SIZE_DIM0 && 
        inRowCol.getCol() <= IMAGE_SIZE_DIM1)
    {
        image[inRowCol.getRow()][inRowCol.getCol()].setTo(inColor);
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
        inRowCol.getRow() <= IMAGE_SIZE_DIM0 && 
        inRowCol.getCol() <= IMAGE_SIZE_DIM1)
    {
        outColor.setTo(image[inRowCol.getRow()][inRowCol.getCol()]);
        return true;
    }
    else
    {
        return false;
    }

}

//This method prints the contents of the image to the screen.
void ColorImageClass::printImage()
{
    int cntRow;
    int cntCol;

    for (cntRow = 0; cntRow < IMAGE_SIZE_DIM0; cntRow++)
    {
        for (cntCol = 0; cntCol < IMAGE_SIZE_DIM1 - 1; cntCol++)
        {
            image[cntRow][cntCol].printComponentValues();
            cout << "--";
        }
        image[cntRow][cntCol].printComponentValues();
    }
}