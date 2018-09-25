#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}


void Input::GetPointClicked(double &x, double &y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output *pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if (Key == 8 && Label.size() != 0)	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction(BarType BT) const
{
	double x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	UI.LastPoint.x = x;
	UI.LastPoint.y = y;

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check which Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on


			switch (ClickedItemOrder)
			{
			case PLAY_MODE: return TO_PLAY;

			case ITM_RECT: return DRAW_RECT;

			case ITM_CIRC: return DRAW_CIRC;

			case ITM_TRI: return DRAW_TRI;

			case ITM_LINE: return DRAW_LINE;

			case ITM_CHNG_CLR: return CHNG_CLR;

			case ITM_BORDER_WDTH: return CHNG_BORDER_WIDTH;

			case ITM_ZOOM: return ZOOM;

			case ITM_SELECT: return SELECT;

			case ITM_MOVE:	return MOVE;

			case ITM_RESIZE: return RESIZE;

			case ITM_ROTATE: return ROTATE;

			case ITM_SEND_BK: return SEND_BACK;

			case ITM_BRNG_FRNT: return BRNG_FRNT;

			case ITM_COPY: return COPY;

			case ITM_CUT: return CUT;

			case ITM_PASTE: return PASTE;

			case ITM_DLT_FIG: return DEL;

			case ITM_UNDO: return UNDO;

			case ITM_REDO: return REDO;

			case ITM_SAVE: return SAVE;

			case ITM_LOAD: return LOAD;

			case ITM_EXIT: return EXIT;

			default: return EMPTY;

			}
		}
		//[2] User clicks on the drawing area
		if (y >= (UI.ToolBarHeight) && y < (UI.height - UI.StatusBarHeight))
		{
			switch (BT)
			{
			case RESIZEBAR:
				if (x > ITM_RESIZE*UI.MenuItemWidth && x < (ITM_RESIZE + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return RESIZEBY1_4;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return RESIZEBY1_2;
					if (y > (3 * UI.ToolBarHeight) && y < (4 * UI.ToolBarHeight))
						return RESIZEBY2;
					if (y > (4 * UI.ToolBarHeight) && y < (5 * UI.ToolBarHeight))
						return RESIZEBY4;
				}
				break;
			case ROTATEBAR:
				if (x > ITM_ROTATE*UI.MenuItemWidth && x < (ITM_ROTATE + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return ROTATEBY90;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return ROTATEBY270;
					if (y > (3 * UI.ToolBarHeight) && y < (4 * UI.ToolBarHeight))
						return ROTATEBY180;
				}
				break;
			case ZOOMBAR:
				if (x > ITM_ZOOM*UI.MenuItemWidth && x < (ITM_ZOOM + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return ZOOMOUT;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return ZOOMIN;
				}
				break;

			case CHANGECOLORBAR:
				if (x > ITM_CHNG_CLR*UI.MenuItemWidth && x < (ITM_CHNG_CLR + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return CHANGEBACKGROUNDCOLOR;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return CHANGEFILLCOLOR;
					if (y > (3 * UI.ToolBarHeight) && y < (4 * UI.ToolBarHeight))
						return CHANGEDRAWCOLOR;
				}
				break;
			case CHANGEBORDERWEIDTHBAR:
				if (x > ITM_BORDER_WDTH*UI.MenuItemWidth && x < (ITM_BORDER_WDTH + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return BORDERBY1;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return BORDERBY3;
					if (y > (3 * UI.ToolBarHeight) && y < (4 * UI.ToolBarHeight))
						return BORDERBY8;
					if (y > (4 * UI.ToolBarHeight) && y < (5 * UI.ToolBarHeight))
						return BORDERBY12;
				}
				break;
			}
			return DRAWING_AREA;
		}

		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			switch (ClickedItemOrder)
			{
			case DRAW_MODE: return TO_DRAW;

			case PICKandHIDE: return PICKANDHIDE_GAME;

			case SCRAMBLEandFIND: return SCRAMBLEANDFIND_GAME;

			default: return DRAWING_AREA;
			}
		}
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			if (BT == PICKANDHIDEBAR)
				if (x > PICKandHIDE*UI.MenuItemWidth && x < (PICKandHIDE + 1)*UI.MenuItemWidth)
				{
					if (y > (1 * UI.ToolBarHeight) && y < (2 * UI.ToolBarHeight))
						return PICKBYTYPE;
					if (y > (2 * UI.ToolBarHeight) && y < (3 * UI.ToolBarHeight))
						return PICKBYTYPEANDFILLCOLOR;
					if (y > (3 * UI.ToolBarHeight) && y < (4 * UI.ToolBarHeight))
						return PICKBYAREA;
					if (y > (4 * UI.ToolBarHeight) && y < (5 * UI.ToolBarHeight))
						return PICKBYFILLCOLOR;
				}
			return DRAWING_AREA;
		}
		return STATUS;
	}
}


ActionType Input::GetExitAction()const
{
	double x, y;
	do
	{
		pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click
	} while (!((x>10 && x < 95 && y>90 && y<135) || (x>100 && x < 250 && y>90 && y<135) || (x>255 && x < 370 && y>90 && y<135)));

	delete pWind;

	if (x > 10 && x < 95)
		return SAVE;
	else if (x > 100 && x < 250)
		return EXIT;
	else
		return DRAWING_AREA;
}


color* Input::getColor() const
{
	double x, y;
	pWind->WaitMouseClick(x, y);
	if (x > UI.ColorWidth || y >= UI.height - UI.StatusBarHeight || y < UI.ToolBarHeight)
		return NULL;
	int ClickedItemOrder = ((y - UI.ToolBarHeight) / UI.ColorHeight);
	return &UI.BarColors[ClickedItemOrder];
}


int Input::getBorderWidth(Output *pO) const
{
	return stoi(GetSrting(pO));
}

Point Input::GetLastPoint() const
{
	return UI.LastPoint;
}

/////////////////////////////////



Input::~Input()
{
}
