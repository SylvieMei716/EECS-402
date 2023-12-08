#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ColorClass.h"
#include "constants.h"

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains implementations of 
//all the ColorClass methods.

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
    if (inRed >= MIN_COLOR_VALUE && inRed <= MAX_COLOR_VALUE &&
        inGreen >= MIN_COLOR_VALUE && inGreen <= MAX_COLOR_VALUE && 
        inBlue >= MIN_COLOR_VALUE && inBlue <= MAX_COLOR_VALUE)
    {
        redValue = inRed;
        greenValue = inGreen;
        blueValue = inBlue;
        return true;
    }
    else
    {
        return false;
    }
    
}

//This method sets the color object according to input ColorClass object.
//If "clipping" is needed, it returns true; elsewise, it returns false.
bool ColorClass::setTo(ColorClass &inColor)
{
    return setTo(inColor.redValue, inColor.greenValue, inColor.blueValue);
}

//This method sets the object's color according to the index user inputs.
void ColorClass::setTo(int inputColor)
{
    if (inputColor == INDEX_OF_RED)
    {
        setToRed();
    }
    if (inputColor == INDEX_OF_GREEN)
    {
        setToGreen();
    }
    if (inputColor == INDEX_OF_BLUE)
    {
        setToBlue();
    }
    if (inputColor == INDEX_OF_BLACK)
    {
        setToBlack();
    }
    if (inputColor == INDEX_OF_WHITE)
    {
        setToWhite();
    }
}

//This method gets the object's red value.
int ColorClass::getRed()
{
    return redValue;
}

//This method gets the object's green value.
int ColorClass::getGreen()
{
    return greenValue;
}

//This method gets the object's blue value.
int ColorClass::getBlue()
{
    return blueValue;
}

//This method prints out the object's RGB value to a file.
void ColorClass::printComponentValues(ostream &outStream)
{
    outStream << redValue << " " << greenValue << " " 
         << blueValue  << " " << endl;
}

//This method verifies whether two objects have the same color.
bool ColorClass::isTheSameColor(ColorClass rhsColor)
{
    if (redValue == rhsColor.getRed() && 
        greenValue == rhsColor.getGreen() && 
        blueValue == rhsColor.getBlue())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//This method reads RGB value for an object from a ppm file.
bool ColorClass::readColorFromFile(istream &inFile)
{
    int red, green, blue;

    inFile >> red;
    if (red < MIN_COLOR_VALUE || red > MAX_COLOR_VALUE) 
    {
        cout << "Error: Invalid red value." << endl;
        return false;
    }
    inFile >> green;
    if (green < MIN_COLOR_VALUE || green > MAX_COLOR_VALUE) 
    {
        cout << "Error: Invalid green value." << endl;
        return false;
    }
    inFile >> blue;
    if (blue < MIN_COLOR_VALUE || blue > MAX_COLOR_VALUE) 
    {
        cout << "Error: Invalid blue value." << endl;
        return false;
    }

    setTo(red, green, blue);
    return true;
}