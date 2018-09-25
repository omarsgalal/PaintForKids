#include "Output.h"

Output::Output()
{
	//Initialize user interface parameters
	
	UI.InterfaceMode = MODE_DRAW;

	UI.width = 1520;
	UI.height = 750;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 66;
	UI.ColorWidth = 25;

	UI.DrawColor = BLUE;			//Drawing color
	UI.FillColor = GREEN;			//Filling color
	UI.MsgColor = WHITE;			//Messages color
	UI.BkGrndColor = PALE;			//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = DOWN;       //Status Bar color 
	UI.PlayBarColor = SALMON;		//Play Bar color 
	UI.ColorBarColor = SNOW;		//ColorBar color 
	UI.ToolBarColor = WHITE;		//Tool Bar color 
	UI.PenWidth = 3;	//width of the figures frames
	UI.ZoomFactor = 1;

	//Barcolor: Array of colors consists of 20 color 
	UI.BarColors[0] = PINK;
	UI.BarColors[1] = BROWN;
	UI.BarColors[2] = WHITE;
	UI.BarColors[3] = BISQUE;
	UI.BarColors[4] = BLUE;
	UI.BarColors[5] = LINEN;
	UI.BarColors[6] = RED;
	UI.BarColors[7] = BLACK;
	UI.BarColors[8] = YELLOW;
	UI.BarColors[9] = GREEN;
	UI.BarColors[10] = SLATEGRAY;
	UI.BarColors[11] = PEACHPUFF;
	UI.BarColors[12] = MEDIUMTURQUOISE;
	UI.BarColors[13] = PALE;
	UI.BarColors[14] = SIENNA;
	UI.BarColors[15] = PURPLE;
	UI.BarColors[16] = DARKMAGENTA;
	UI.BarColors[17] = DARKVIOLET;
	UI.BarColors[18] = PALEVIOLETRED;
	UI.BarColors[19] = ORANGE;
	UI.BarColors[20] = LIGHTPINK;

	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);

	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	//Create Draw tool Bar
	CreateDrawToolBar();

	//Create Status Bar 
	CreateStatusBar();

}

//this function clears the tool bar 
void Output::ClearToolBar() const {
	pWind->SetPen(UI.ToolBarColor, 1);
	pWind->SetBrush(UI.ToolBarColor);
	pWind->DrawRectangle(0, 0, UI.width, UI.ToolBarHeight);
}

//this function creates a pointer to input to access input member functions
Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

//this funtion creates new window  
window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);

	return pW;
}

Input* Output::CreateExitWindow()const
{
	int width = 400, height = 170;

	//Create the output window
	window*wind = CreateWind(width, height, 500, 300);

	//Change the title
	wind->ChangeTitle("Panit for Kids");

	wind->SetPen(UI.StatusBarColor, 1);
	wind->SetBrush(MAROON);

	wind->DrawRectangle(0, 0, width, height);

	wind->SetPen(WHITE, 0.5);
	wind->SetBrush(WHITE);

	wind->SetFont(20, BOLD, SCRIPT);
	wind->DrawString(15, 30, "Graph is not Saved. Do you want to Save it? ");

	wind->SetPen(MAROON, 0.5);
	wind->SetFont(25, BOLD, SCRIPT);

	wind->DrawRectangle(10, 90, 95, 135, FILLED);
	wind->DrawString(25, 100, "Save");

	wind->DrawRectangle(100, 90, 250, 135, FILLED);
	wind->DrawString(120, 100, "Don't Save");


	wind->DrawRectangle(255, 90, 370, 135, FILLED);
	wind->DrawString(275, 100, "Cancel");

	return new Input(wind);
}

//this function creates status bar
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//this functio clears status bar
void Output::ClearStatusBar()
{
	PreviousMsg = "";
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}

//this function creates draw tool bar 
void Output::CreateDrawToolBar(int undo, int redo) const
{

	//MenuItemImages: Array of strings contain tool bar 1 icons paths
	string MenuItemImages[DRAW_ITM_COUNT];

	MenuItemImages[PLAY_MODE] = "images\\MenuItems\\play.jpg";
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\rectangle.jpg";
	MenuItemImages[ITM_CIRC] = "images\\MenuItems\\circle.jpg";
	MenuItemImages[ITM_TRI] = "images\\MenuItems\\triangle.jpg";
	MenuItemImages[ITM_LINE] = "images\\MenuItems\\line.jpg";
	MenuItemImages[ITM_CHNG_CLR] = "images\\MenuItems\\changeclr.jpg";
	MenuItemImages[ITM_BORDER_WDTH] = "images\\MenuItems\\Width.jpg";
	MenuItemImages[ITM_SELECT] = "images\\MenuItems\\select.jpg";
	MenuItemImages[ITM_RESIZE] = "images\\MenuItems\\resize.jpg";
	MenuItemImages[ITM_ZOOM] = "images\\MenuItems\\zoom.jpg";
	MenuItemImages[ITM_MOVE] = "images\\MenuItems\\move.jpg";
	MenuItemImages[ITM_COPY] = "images\\MenuItems\\copy.jpg";
	MenuItemImages[ITM_CUT] = "images\\MenuItems\\cut.jpg";
	MenuItemImages[ITM_PASTE] = "images\\MenuItems\\paste.jpg";
	MenuItemImages[ITM_DLT_FIG] = "images\\MenuItems\\delete.jpg";
	MenuItemImages[ITM_SAVE] = "images\\MenuItems\\save.jpg";
	MenuItemImages[ITM_LOAD] = "images\\MenuItems\\load.jpg";
	MenuItemImages[ITM_SEND_BK] = "images\\MenuItems\\Send_Back.jpg";
	MenuItemImages[ITM_BRNG_FRNT] = "images\\MenuItems\\bring_front.jpg";
	MenuItemImages[ITM_ROTATE] = "images\\MenuItems\\rotate.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Exit.jpg";

	if ((undo == -1 && redo == -1) || (undo == 0 && redo == 0))
	{
		MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undodisabled.jpg";
		MenuItemImages[ITM_REDO] = "images\\MenuItems\\redodisabled.jpg";
	}
	else if (undo == 1 && redo == 0)
	{
		MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undoenabled.jpg";
		MenuItemImages[ITM_REDO] = "images\\MenuItems\\redodisabled.jpg";
	}
	else if (undo == 0 && redo == 1)
	{
		MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undodisabled.jpg";
		MenuItemImages[ITM_REDO] = "images\\MenuItems\\redoenabled.jpg";
	}
	else
	{
		MenuItemImages[ITM_UNDO] = "images\\MenuItems\\undoenabled.jpg";
		MenuItemImages[ITM_REDO] = "images\\MenuItems\\redoenabled.jpg";
	}

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);

	//Draw a line under the toolbar
	pWind->SetPen(LINE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);

}

//this function creates play bar
void Output::CreatePlayToolBar() const
{

	//MenuItemImages: Array of strings contain play bar icons paths
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[DRAW_MODE] = "images\\MenuItems\\draw.jpg";
	MenuItemImages[PICKandHIDE] = "images\\MenuItems\\PICK.jpg";
	MenuItemImages[SCRAMBLEandFIND] = "images\\MenuItems\\SCRAMBLE.jpg";

	//Draw menu item one image at a time
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i*UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);


	//Draw a line under the toolbar
	pWind->SetPen(LINE, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);
}

//this function creates color bar 
void Output::CreateColorBar() const
{
	//Adjust every color button's width 
	UI.ColorHeight = float(UI.height - UI.StatusBarHeight - UI.ToolBarHeight) / 20;
	for (int i = 0; i < 20; i++)
	{
		//adjust properties of each color in the array of colors to be drawn as a rectangle
		pWind->SetPen(UI.BarColors[i], 3);
		pWind->SetBrush(UI.BarColors[i]);
		pWind->DrawRectangle(0, UI.ToolBarHeight + i*UI.ColorHeight, UI.ColorWidth, UI.ToolBarHeight + (i + 1)*UI.ColorHeight);
	}
}

void Output::CreateDoneIcon() const
{
	pWind->DrawImage("images\\MenuItems\\Done.jpg", (SELECT + 1)*UI.MenuItemWidth, 0, UI.MenuItemWidth - 3, UI.ToolBarHeight - 2);
}

void Output::CreateUnselectAllIcon() const
{
	pWind->DrawImage("images\\MenuItems\\unselectall.jpg", (SELECT + 1)*UI.MenuItemWidth, 0, UI.MenuItemWidth - 3, UI.ToolBarHeight - 2);
}

//this function clears draw area 
void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);
}


void Output::PrintMessage(string msg)	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	PreviousMsg = msg;
	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}

void Output::UpdateStatusBar()
{
	PrintMessage(PreviousMsg);
}

int Output::GetWidth() const
{
	return UI.width;
}

int Output::GetHeight() const
{
	return UI.height;
}

int Output::GetStatusBarHeight() const
{
	return UI.StatusBarHeight;
}

int Output::GetToolBarHeight() const
{
	return UI.ToolBarHeight;
}

int Output::GetMenuItemWidth() const
{
	return UI.MenuItemWidth;
}

int Output::GetColorWidth() const
{
	return UI.ColorWidth;
}

void Output::SetCrntDrawColor(const color c)
{
	UI.DrawColor = c;
}

color Output::getCrntDrawColor() const	//get current drwawing color
{
	return UI.DrawColor;
}

void Output::SetCrntFillColor(const color c)
{
	UI.FillColor = c;
}

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}

void Output::SetCrntBkgroundColor(const color c)
{
	UI.BkGrndColor = c;
}


color Output::getBkgroundColor() const
{
	return UI.BkGrndColor;
}

void Output::SetStatusBarColor(color c)
{
	UI.StatusBarColor = c;
}

color Output::GetStatusBarColor()
{
	return UI.StatusBarColor;
}

void Output::SetFilled(bool filled)
{
	UI.Filled = filled;
}

bool Output::isFilled() const
{
	return UI.Filled;
}

void Output::SetZoomFactor(int Zoom)
{
	UI.ZoomFactor = Zoom;
}

int Output::GetZoomFactor() const
{
	return UI.ZoomFactor;
}

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

void Output::SetCrntPenWidth(int Pen)
{
	UI.PenWidth = Pen;
}

color Output::GetColorByIndex(int index) const
{
	return UI.BarColors[index];
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const		//Draw figure of type Rectangle
{

	P1.x -= 0.5*UI.width;
	P1.y -= 0.5*UI.height;
	P2.x -= 0.5*UI.width;
	P2.y -= 0.5*UI.height;
	P1.x = (P1.x) * sqrt(UI.ZoomFactor);
	P1.y = (P1.y) * sqrt(UI.ZoomFactor);
	P2.x = (P2.x) * sqrt(UI.ZoomFactor);
	P2.y = (P2.y) * sqrt(UI.ZoomFactor);
	P1.x += 0.5*UI.width;
	P1.y += 0.5*UI.height;
	P2.x += 0.5*UI.width;
	P2.y += 0.5*UI.height;

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth* sqrt(UI.ZoomFactor));	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);
}

void Output::Drawtriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected) const  //Draw figure of type triangle
{
	P1.x -= 0.5*UI.width;
	P1.y -= 0.5*UI.height;
	P2.x -= 0.5*UI.width;
	P2.y -= 0.5*UI.height;
	P3.x -= 0.5*UI.width;
	P3.y -= 0.5*UI.height;
	P1.x = (P1.x) * sqrt(UI.ZoomFactor);
	P1.y = (P1.y) * sqrt(UI.ZoomFactor);
	P2.x = (P2.x) * sqrt(UI.ZoomFactor);
	P2.y = (P2.y) * sqrt(UI.ZoomFactor);
	P3.x = (P3.x) * sqrt(UI.ZoomFactor);
	P3.y = (P3.y) * sqrt(UI.ZoomFactor);
	P1.x += 0.5*UI.width;
	P1.y += 0.5*UI.height;
	P2.x += 0.5*UI.width;
	P2.y += 0.5*UI.height;
	P3.x += 0.5*UI.width;
	P3.y += 0.5*UI.height;

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth* sqrt(UI.ZoomFactor));	//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}

void Output::Drawline(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const // Draw figure of type Line
{
	P1.x -= 0.5*UI.width;
	P1.y -= 0.5*UI.height;
	P2.x -= 0.5*UI.width;
	P2.y -= 0.5*UI.height;
	P1.x = (P1.x) * sqrt(UI.ZoomFactor);
	P1.y = (P1.y) * sqrt(UI.ZoomFactor);
	P2.x = (P2.x) * sqrt(UI.ZoomFactor);
	P2.y = (P2.y) * sqrt(UI.ZoomFactor);
	P1.x += 0.5*UI.width;
	P1.y += 0.5*UI.height;
	P2.x += 0.5*UI.width;
	P2.y += 0.5*UI.height;

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth* sqrt(UI.ZoomFactor));	//Set Drawing color & width

	pWind->DrawLine(P1.x, P1.y, P2.x, P2.y);
}

void Output::Drawcircle(Point P1, double r, GfxInfo RectGfxInfo, bool selected) const  //Draw figure of type  circle
{
	P1.x -= 0.5*UI.width;
	P1.y -= 0.5*UI.height;
	P1.x = (P1.x) * sqrt(UI.ZoomFactor);
	P1.y = (P1.y)* sqrt(UI.ZoomFactor);
	r = r* sqrt(UI.ZoomFactor);
	P1.x += 0.5*UI.width;
	P1.y += 0.5*UI.height;

	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;		 //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, RectGfxInfo.BorderWdth* sqrt(UI.ZoomFactor));			//Set Drawing color & width

	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;

	pWind->DrawCircle(P1.x, P1.y, r, style);
}



void Output::CreateResizeBar() const
{
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\quarter.jpg", ITM_RESIZE*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\half.jpg", ITM_RESIZE*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\two.jpg", ITM_RESIZE*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ResizeBar\\four.jpg", ITM_RESIZE*UI.MenuItemWidth, 4 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreateBorderBar() const
{
	pWind->DrawImage("images\\MenuItems\\BorderWidthBar\\1.jpg", ITM_BORDER_WDTH*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\BorderWidthBar\\3.jpg", ITM_BORDER_WDTH*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\BorderWidthBar\\5.jpg", ITM_BORDER_WDTH*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\BorderWidthBar\\7.jpg", ITM_BORDER_WDTH*UI.MenuItemWidth, 4 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreateZoomBar() const
{
	pWind->DrawImage("images\\MenuItems\\ZoomBar\\zoom-out.jpg", ITM_ZOOM*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ZoomBar\\zoom-in.jpg", ITM_ZOOM*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreateRotateBar() const
{
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate_90_ccw.jpg", ITM_ROTATE*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate_90_cw.jpg", ITM_ROTATE*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\RotateBar\\rotate_180.jpg", ITM_ROTATE*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreateChangeClrBar() const
{
	pWind->DrawImage("images\\MenuItems\\ChangColorBar\\background.jpg", ITM_CHNG_CLR*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ChangColorBar\\colorfill.jpg", ITM_CHNG_CLR*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\ChangColorBar\\bordercolor.jpg", ITM_CHNG_CLR*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

void Output::CreatePickAndHideBar()const
{
	pWind->DrawImage("images\\MenuItems\\PickAndHideBar\\bytype.jpg", PICKandHIDE*UI.MenuItemWidth, UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\PickAndHideBar\\bytypeandfill.jpg", PICKandHIDE*UI.MenuItemWidth, 2 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\PickAndHideBar\\byarea.jpg", PICKandHIDE*UI.MenuItemWidth, 3 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->DrawImage("images\\MenuItems\\PickAndHideBar\\byfill.jpg", PICKandHIDE*UI.MenuItemWidth, 4 * UI.ToolBarHeight + 2, UI.MenuItemWidth, UI.ToolBarHeight);
}

int Output::GetColorIndex(color c) const
{
	return UI.GetColorIndex(c);
}

void Output::SetInterfaceMode(GUI_MODE Mode)
{
	UI.InterfaceMode = Mode;
}

GUI_MODE Output::GetInterfaceMode()
{
	return UI.InterfaceMode;
}

Output::~Output()
{
	delete pWind;
}

