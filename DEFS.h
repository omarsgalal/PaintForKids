#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contais some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_LINE,		//Draw Line
	DRAW_RECT,		//Draw Rectangle
	DRAW_TRI,		//Draw Triangle
	DRAW_CIRC,		//Draw Circle

	CHNG_CLR,	//Change the drawing color  /// check
	//CHNG_FILL_CLR,	//Change the filling color
	//CHNG_BK_CLR,	//Change background color
	CHNG_BORDER_WIDTH,

	ZOOM,
	SELECT,
	MOVE,			//Move a figure(s)
	RESIZE,			//Resize a figure(s)
	ROTATE,			//Rotate a figure(s)
	SEND_BACK,		//Send a figure to the back of all figures
	BRNG_FRNT,		//Bring a figure to the front of all figures

	COPY,
	CUT,
	PASTE,
	DEL,			//Delete a figure(s)

	UNDO,
	REDO,

	SAVE,			//Save the whole graph to a file
	LOAD,			//Load a graph from a file
	EXIT,			//Exit the application

	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status 

	EMPTY,			//A click on empty place in the toolbar

	PICKANDHIDE_GAME,
	SCRAMBLEANDFIND_GAME,

	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,			//Switch interface to Play mode


	RESIZEBY1_4,
	RESIZEBY1_2,
	RESIZEBY2,
	RESIZEBY4,
	ZOOMIN,
	ZOOMOUT,
	ROTATEBY90,
	ROTATEBY180,
	ROTATEBY270,
	PICKBYAREA,
	PICKBYTYPE,
	PICKBYFILLCOLOR,
	PICKBYTYPEANDFILLCOLOR,
	BORDERBY1,
	BORDERBY3,
	BORDERBY8,
	BORDERBY12,
	CHANGEBACKGROUNDCOLOR,
	CHANGEDRAWCOLOR,
	CHANGEFILLCOLOR

	///TODO: Add more action types (if needed)
};

enum BarType
{
	RESIZEBAR,
	ROTATEBAR,
	ZOOMBAR,
	PICKANDHIDEBAR,
	CHANGECOLORBAR,
	CHANGEBORDERWEIDTHBAR,
	NOBAR
};

struct Point	//To be used for figures points
{ double x,y; };

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif