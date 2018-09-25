#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
	string PreviousMsg;
public:
	Output();

	window* CreateWind(int, int, int, int) const; //creates the application window
	Input* CreateExitWindow()const;	//creates Window to Check User wants to save Graph or not
	void CreateDrawToolBar(int=-1,int=-1) const;	//creates Draw mode toolbar & menu
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu
	void CreateStatusBar() const;	//create the status bar
	void CreateColorBar() const;	//create the color bar
	void CreateResizeBar() const; //create resize bar of the ratios available
	void CreateBorderBar() const; //create Border width bar of the ratios available
	void CreateRotateBar() const;  //create rotate bar of the degrees
	void CreateDoneIcon() const;
	void CreateZoomBar() const;
	void CreateChangeClrBar() const;
	void CreatePickAndHideBar()const;
	void CreateUnselectAllIcon()const;

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar();	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area
	void ClearToolBar() const;

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle																					  ///Make similar functions for drawing all other figures.
	void Drawtriangle(Point P1, Point P2, Point P3, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a triangle
	void Drawline(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a line
	void Drawcircle(Point P1, double r, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a circle

	void PrintMessage(string msg);	//Print a message on Status bar
	void UpdateStatusBar();

	int GetWidth()const;
	int GetHeight()const;
	int GetStatusBarHeight()const;
	int GetToolBarHeight()const;
	int GetMenuItemWidth()const;
	int GetColorWidth()const;

	void SetCrntDrawColor(const color);
	color getCrntDrawColor() const;	//get current drwawing color
	void SetCrntFillColor(const color);
	color getCrntFillColor() const;	//get current filling color
	void SetCrntBkgroundColor(const color);
	color getBkgroundColor() const; ////get current Background color
	void SetStatusBarColor(color c);
	color GetStatusBarColor();

	void SetFilled(bool filled);
	bool isFilled()const;

	void SetZoomFactor(int Zoom);
	int GetZoomFactor()const;


	int getCrntPenWidth() const;		//get current pen width
	void SetCrntPenWidth(int);

	color GetColorByIndex(int index) const;
	int GetColorIndex(color c)const;

	void SetInterfaceMode(GUI_MODE);
	GUI_MODE GetInterfaceMode();

	~Output();
};

#endif