#ifndef _COLORCLASS_H_
#define _COLORCLASS_H_

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains definitions of 
//all the ColorClass methods.

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
        void setTo(int inputColor);

        //Print the component color values to the console
        void printComponentValues(ostream &outStream);

        //Print the object's red/green/blue values
        int getRed();
        int getGreen();
        int getBlue();

        //Verifies whether two objects have the same color.
        bool isTheSameColor(ColorClass rhsColor);

        //Reads RGB value for an object from a ppm file.
        bool readColorFromFile(istream &inFile);


    private:
        //Attributes of the object: RGB value
        int redValue;
        int greenValue;
        int blueValue;

};

#endif // _COLORCLASS_H_