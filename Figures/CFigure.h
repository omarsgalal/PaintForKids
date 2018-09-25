#ifndef CFIGURE_H
#define CFIGURE_H

#define POINTINBOUNDARIES {800,60}

#include "..\defs.h"
#include "..\GUI\Output.h"
#include <fstream>
#include <time.h>

enum TYPE
{
	TRECTANGLE,
	TCIRCLE,
	TTRIANGLE,
	TLINE
};

//Base class for all figures
class CFigure
{
protected:
	
	int ID;		//Each figure has an ID
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	static int FigureCount;

public:
	CFigure(GfxInfo FigureGfxInfo, int id = 0);
	CFigure();

	static void LoadFigureCount();
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	int GetBorderwidth()const;
	virtual Point GetCenter() const=0;
	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	void ChngBorderWidth(int borderWidth);	//changes the figure's border width

	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	

	virtual bool Rotate(Output*, int) = 0;	//Rotate the figure
	virtual bool Resize(Output*,float) = 0;	//Resize the figure
	virtual bool Move(Output*, double, double) = 0;		//Move the figure
	virtual bool CheckCoordinates(double, double) = 0;
	virtual void RandomCoordinates(Output* pOut) = 0;
	virtual void ResizeHalfLeft() = 0;
	virtual void Save(ofstream &OutFile, Output* pOut) = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile, Output* pOut) = 0;	//Load the figure parameters to the file
	virtual TYPE GetType() = 0;	//returns the type of the figure
	virtual double GetArea() = 0;	//returns the area of the figure
	virtual CFigure* Copy(bool = false) = 0;	//create an object with the same info of the old one
	virtual void PrintInfo(Output* pOut) = 0;	//print all figure info on the status bar

	void rotatePoint(Point Center, Point &rotatedPoint, int);
	void resizeLine(Point Center, Point&resizedPoint, double Ratio);
	bool CheckInBoundries(Output* pOut, Point P1, Point P2, Point P3 = POINTINBOUNDARIES , int Indicator =1) const;

	int GetID() const;
	color GetFillColor() const;	//returns the fill color of the figure
	void setFilled(bool isFilled);
	bool isFilled();
	color GetBorderColor() const;	//returns the fill color of the figure

};

#endif