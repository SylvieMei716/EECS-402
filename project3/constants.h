#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_

#include <string>
using namespace std;

//Programmer: Xinyu Mei
//Date: 10/19/2023
//Purpose: This file contains definitions of 
//all the global constants used in the image processing project.

const int MENU_ANNOTATE_RECTANGLE = 1;
const int MENU_ANNOTATE_PATTERN = 2;
const int MENU_INSERT_IMAGE = 3;
const int MENU_WRITE_OUT_IMAGE = 4;
const int MENU_EXIT_PROGRAM = 5;
const int DRAW_RECTANGLE_TWO_CORNERS = 1;
const int DRAW_RECTANGLE_CORNER_DIMS = 2;
const int DRAW_RECTANGLE_CENTER = 3;
const int INDEX_OF_RED = 1;
const int INDEX_OF_GREEN = 2;
const int INDEX_OF_BLUE = 3;
const int INDEX_OF_BLACK = 4;
const int INDEX_OF_WHITE = 5;
const int NOT_FILL_RECTANGLE = 1;
const int DO_FILL_RECTANGLE = 2;
const string STANDARD_MAGIC_NUMBER = "P3";
const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;
const int INITIAL_ROW = -99999;
const int INITIAL_COL = -99999;
const int IMAGE_SIZE_MIN = 0;
const int IMAGE_IGNORE_SIZE = 200;

#endif //_CONSTANTS_H_