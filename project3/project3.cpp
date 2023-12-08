#include <iostream>
#include <string>
#include <fstream>
#include "constants.h"
#include "ColorClass.h"
#include "RowColumnClass.h"
#include "ColorImageClass.h"
#include "printColorChoices.h"
using namespace std;

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file is used for users to process images.

string ppmFileToLoad;
string patternFile;
string imageFile;
string ppmFileToSave;
int mainMenuChoice;
int drawRectangleMethod;
int inputColor;
ColorClass borderColor;
ColorClass patternColor;
ColorClass transparencyColor;
int ifFillRectangle;
RowColumnClass upperLeftCorner;
RowColumnClass lowerRightCorner;
RowColumnClass center;
int inputRow;
int inputCol;
int height;
int width;
int halfHeight;
int halfWidth;
bool validInput;
bool exitProgram = false;

int main()
{
    cout << "Enter string for PPM image file name to load: ";
    cin >> ppmFileToLoad;
    ColorImageClass currentImage;
    //Verify whether the file is valid ppm file
    while (!currentImage.readPPMFile(ppmFileToLoad))
    {
        cout << "Please enter again: ";
        cin >> ppmFileToLoad;
    }
    
    while (!exitProgram)
    {
        cout << MENU_ANNOTATE_RECTANGLE 
             << ". Annotate image with rectangle" << endl;
        cout << MENU_ANNOTATE_PATTERN 
             << ". Annotate image with pattern from file" << endl;
        cout << MENU_INSERT_IMAGE << ". Insert another image" << endl;
        cout << MENU_WRITE_OUT_IMAGE << ". Write out current image" << endl;
        cout << MENU_EXIT_PROGRAM << ". Exit the program" << endl;
        cout << "Enter int for main menu choice: ";
        validInput = false;

        while (!validInput)
        {
            cin >> mainMenuChoice;
            if (cin.fail() || 
                !(mainMenuChoice == MENU_ANNOTATE_RECTANGLE || 
                mainMenuChoice == MENU_ANNOTATE_PATTERN || 
                mainMenuChoice == MENU_INSERT_IMAGE || 
                mainMenuChoice == MENU_WRITE_OUT_IMAGE || 
                mainMenuChoice == MENU_EXIT_PROGRAM))
            {
                cin.clear();
                cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                cout << "That's not a valid choice! Please enter again: ";
            }
            else
            {
                validInput = true;
            }
        }

        if (mainMenuChoice == MENU_ANNOTATE_RECTANGLE)
        {
            cout << DRAW_RECTANGLE_TWO_CORNERS 
                 << ". Specify upper left and lower right corners of rectangle" 
                 << endl;
            cout << DRAW_RECTANGLE_CORNER_DIMS 
                 << ". Specify upper left corner and dimensions of rectangle"
                 << endl;
            cout << DRAW_RECTANGLE_CENTER 
                 << ". Specify extent from center of rectangle"
                 << endl;
            cout << "Enter int for rectangle specification method: ";
            validInput = false;

            while(!validInput)
            {
                cin >> drawRectangleMethod;
                if (cin.fail() || 
                    !(drawRectangleMethod == DRAW_RECTANGLE_TWO_CORNERS || 
                    drawRectangleMethod == DRAW_RECTANGLE_CORNER_DIMS || 
                    drawRectangleMethod == DRAW_RECTANGLE_CENTER))
                {
                    cin.clear();
                    cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                    cout << "That's not a valid choice! Please enter again: ";
                }
                else
                {
                    validInput = true;
                }
            }
            if (drawRectangleMethod == DRAW_RECTANGLE_TWO_CORNERS)
            {
                cout << "Enter upper left corner row and column: ";
                cin >> inputRow >> inputCol;
                upperLeftCorner.setRowCol(inputRow, inputCol);
                cout << "Enter lower right corner row and column: ";
                cin >> inputRow >> inputCol;
                lowerRightCorner.setRowCol(inputRow, inputCol);
            }

            if (drawRectangleMethod == DRAW_RECTANGLE_CORNER_DIMS)
            {
                cout << "Enter upper left corner row and column: ";
                cin >> inputRow >> inputCol;
                upperLeftCorner.setRowCol(inputRow, inputCol);
                cout << "Enter int for number of rows: ";
                cin >> height;
                cout << "Enter int for number of columns: ";
                cin >> width;
                lowerRightCorner.setRowCol(upperLeftCorner.getRow() + height, 
                                           upperLeftCorner.getCol() + width);
            }

            if (drawRectangleMethod == DRAW_RECTANGLE_CENTER)
            {
                cout << "Enter rectangle center row and column: ";
                cin >> inputRow >> inputCol;
                center.setRowCol(inputRow, inputCol);
                cout << "Enter int for half number of rows: ";
                cin >> halfHeight;
                cout << "Enter int for half number of columns: ";
                cin >> halfWidth;
                upperLeftCorner.setRowCol(center.getRow() - halfWidth, 
                                          center.getCol() - halfHeight);
                lowerRightCorner.setRowCol(center.getRow() + halfWidth, 
                                           center.getCol() + halfHeight);
            }

            printColorChoices();
            cout << "Enter int for rectangle color: ";
            validInput = false;

            while (!validInput)
            {
                cin >> inputColor;
                if (cin.fail() || 
                    !(inputColor == INDEX_OF_RED || 
                    inputColor == INDEX_OF_GREEN || 
                    inputColor == INDEX_OF_BLUE || 
                    inputColor == INDEX_OF_BLACK || 
                    inputColor == INDEX_OF_WHITE))
                {
                    cin.clear();
                    cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                    cout << "That's not a valid choice! Please enter again: ";
                }
                else
                {
                    borderColor.setTo(inputColor);
                    validInput = true;
                }
            }

            cout << NOT_FILL_RECTANGLE << ". No" << endl;
            cout << DO_FILL_RECTANGLE << ". Yes" << endl;
            cout << "Enter int for rectangle fill option: ";
            validInput = false;

            while (!validInput)
            {
                cin >> ifFillRectangle;
                if (cin.fail() || 
                    !(ifFillRectangle == NOT_FILL_RECTANGLE || 
                    ifFillRectangle == DO_FILL_RECTANGLE))
                {
                    cin.clear();
                    cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                    cout << "That's not a valid choice! Please enter again: ";
                }
                else
                {
                    validInput = true;
                }
            }

            currentImage.drawRectangle(upperLeftCorner, 
                                       lowerRightCorner, 
                                       borderColor, 
                                       ifFillRectangle - 1);

        }

        if (mainMenuChoice == MENU_ANNOTATE_PATTERN)
        {
            cout << "Enter string for file name containing pattern: ";
            cin >> patternFile;
            cout << "Enter upper left corner of pattern row and column: ";
            cin >> inputRow >> inputCol;
            upperLeftCorner.setRowCol(inputRow, inputCol);
            printColorChoices();
            cout << "Enter int for pattern color: ";
            validInput = false;

            while (!validInput)
            {
                cin >> inputColor;
                if (cin.fail() || 
                    !(inputColor == INDEX_OF_RED || 
                    inputColor == INDEX_OF_GREEN || 
                    inputColor == INDEX_OF_BLUE || 
                    inputColor == INDEX_OF_BLACK || 
                    inputColor == INDEX_OF_WHITE))
                {
                    cin.clear();
                    cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                    cout << "That's not a valid choice! Please enter again: ";
                }
                else
                {
                    patternColor.setTo(inputColor);
                    validInput = true;
                }
            }

            currentImage.drawPattern(patternFile, 
                                     upperLeftCorner, 
                                     patternColor);
        }

        if (mainMenuChoice == MENU_INSERT_IMAGE)
        {
            cout << "Enter string for file name of PPM image to insert: ";
            cin >> imageFile;
            cout << "Enter upper left corner to insert image row and column: ";
            cin >> inputRow >> inputCol;
            upperLeftCorner.setRowCol(inputRow, inputCol);
            printColorChoices();
            cout << "Enter int for transparency color: ";
            validInput = false;

            while (!validInput)
            {
                cin >> inputColor;
                if (cin.fail() || 
                    !(inputColor == INDEX_OF_RED || 
                    inputColor == INDEX_OF_GREEN || 
                    inputColor == INDEX_OF_BLUE || 
                    inputColor == INDEX_OF_BLACK || 
                    inputColor == INDEX_OF_WHITE))
                {
                    cin.clear();
                    cin.ignore(IMAGE_IGNORE_SIZE, '\n');
                    cout << "That's not a valid choice! Please enter again: ";
                }
                else
                {
                    transparencyColor.setTo(inputColor);
                    validInput = true;
                }
            }

            ColorImageClass imageToInsert;
            imageToInsert.readPPMFile(imageFile);
            currentImage.insertImage(imageToInsert, 
                                     upperLeftCorner, 
                                     transparencyColor);
        }

        if (mainMenuChoice == MENU_WRITE_OUT_IMAGE)
        {
            cout << "Enter string for PPM file name to output: ";
            cin >> ppmFileToSave;
            while (!currentImage.writePPMFile(ppmFileToSave))
            {
                cout << "Please enter again: ";
                cin >> ppmFileToSave;
            }
        }

        if (mainMenuChoice == MENU_EXIT_PROGRAM)
        {
            exitProgram = true;
            cout << "Thank you for using this program" << endl;
        }
    }
    return 0;
}