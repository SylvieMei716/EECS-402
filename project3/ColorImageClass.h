#ifndef _COLORIMAGECLASS_H_
#define _COLORIMAGECLASS_H_

#include <string>
using namespace std;

#include "ColorClass.h"
#include "RowColumnClass.h"

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains definitions of 
//all the ColorImageClass methods.

class ColorImageClass
{

    public:
        //Defaultly set all pixels in the image to full black
        ColorImageClass();
        ~ColorImageClass();

        //Set color at position provided by inRowCol to inColor
        bool setColorAtLocation(
             RowColumnClass &inRowCol,
             ColorClass &inColor
             );

        //Turns the parameter outColor into color at location inRowCol
        bool getColorAtLocation(
             RowColumnClass &inRowCol,
             ColorClass &outColor
             );

        int getWidth();
        int getHeight();

        //Reads in a PPM file
        bool readPPMFile(string filename);

        //Annotates rectangle on the object image
        void drawRectangle(
             RowColumnClass upperLeftCorner,
             RowColumnClass lowerRightCorner,
             ColorClass borderColor,
             bool ifFillRectangle
             );

        //Writes out a PPM file
        bool writePPMFile(string filename);

        //Annotates pattern on the object image
        bool drawPattern(
            string filename, 
            RowColumnClass upperLeftCorner, 
            ColorClass patternColor);

        //Inserts another image on the object image
        bool insertImage(
            ColorImageClass imageToInsert, 
            RowColumnClass upperLeftCorner, 
            ColorClass transparencyColor);

    private:
        //Attribute of objecg: a 2D array of ColorClass objects
        int numRows;
        int numCols;
        ColorClass** imageArr;

};

#endif //_COLORIMAGECLASS_H_