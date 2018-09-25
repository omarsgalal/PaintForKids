#ifndef UI_INFO_H
#define UI_INFO_H

#define colorsNumber 20		//there ara 20 colors in the color bar

#include "..\CMUgraphicsLib\CMUgraphics.h"

//User Interface information file.
//This file contains info that is needed by Input and Output classes to
//handle the user interface

enum GUI_MODE	//Graphical user interface mode
{
	MODE_DRAW,	//Drawing mode (startup mode)
	MODE_PLAY	//Playing mode
};

enum DrawMenuItem //The items of the Draw menu (you should add more items)
{

	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here
	PLAY_MODE,           //Icon for draw mode in the draw mode toolbar 

	ITM_RECT,		//Recangle item in menu
	ITM_CIRC,		//Circle item in menu
	ITM_TRI,        //Triangle item in menu
	ITM_LINE,       //LINE item in menu

	ITM_CHNG_CLR,     //change the color of the background
	ITM_BORDER_WDTH,    //change the width of the border 
	ITM_ZOOM,			 //zoom icon 

	ITM_SELECT,         //select the figures' icon
	ITM_MOVE,           //move icon 
	ITM_RESIZE,         //resize the figures' icon
	ITM_ROTATE,			//rotate icon
	ITM_SEND_BK,
	ITM_BRNG_FRNT,

	ITM_COPY,           //copy icon
	ITM_CUT,			//cut icon
	ITM_PASTE,          //paste icon 
	ITM_DLT_FIG,        //delete figure icon

	ITM_UNDO,
	ITM_REDO,

	ITM_SAVE,			//Save icon 
	ITM_LOAD,			//Load icon

	ITM_EXIT,		//Exit item

	DRAW_ITM_COUNT,	//no. of menu items ==> This should be the last line in this enum

};

enum PlayMenuItem //The items of the Play menu (you should add more items)
{
	//Note: Items are ordered here as they appear in menu
	//If you want to change the menu items order, change the order here

	DRAW_MODE,     //Icon for play mode in the play mode toolbar 
	PICKandHIDE,  // fisrt game 
	SCRAMBLEandFIND,    // second game 

	PLAY_ITM_COUNT		//no. of menu items ==> This should be the last line in this enum

};

enum colors
{
	cPINK,
	cBROWN,
	cWHITE,
	cBISQUE,
	cBLUE,
	cLINEN,
	cRED,
	cBLACK,
	cYELLOW,
	cGREEN,
	cSLATEGRAY,
	cPEACHPUFF,
	cMEDIUMTURQUOISE,
	cPALE,
	cSIENNA,
	cPURPLE,
	cDARKMAGENTA,
	cDARKVIOLET,
	cPALEVIOLETRED,
	cORANGE,
	cLIGHTPINK
};

__declspec(selectany) //This line to prevent "redefinition error"

struct UI_Info	//User Interface Info.
{
	GUI_MODE InterfaceMode;

	int	width, height,	//Window width and height
		wx, wy,			//Window starting coordinates
		StatusBarHeight,	//Status Bar Heightb
		ToolBarHeight,		//Tool Bar Height (distance from top of window to bottom line of toolbar)
		MenuItemWidth,		//Width of each item in toolbar menu
		ColorWidth;			//colorWidth in tool Bar

	float ColorHeight;		//color height in color bar
	int ZoomFactor;

	Point LastPoint;
	color DrawColor;		//Drawing color
	color FillColor;		//Filling color
	color HighlightColor;	//Highlighting color
	color MsgColor;			//Messages color
	color BkGrndColor;		//Background color
	color StatusBarColor;	//Status bar color
	color PlayBarColor;		//Play bar color
	color ToolBarColor;
	color ColorBarColor;	//color bar color
	int PenWidth;			//width of the pen that draws shapes
	bool Filled= false;

	/// Add more members if needed

	color BarColors[colorsNumber];

	int GetColorIndex(color c)
	{
		for (int i = 0; i < colorsNumber; i++)
			if (c == UI.BarColors[i])
				return i;
		return -1;
	}

}UI;	//create a global object UI

#endif