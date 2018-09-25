#pragma once
#include "CFigure.h"
class CTriangle :public CFigure
{
private:
	Point Corner1;
	Point Corner2;
	Point Corner3;
public:
	CTriangle(Point P1, Point P2, Point P3, GfxInfo FigureGfxInfo, int id = 0);
	CTriangle();
	virtual void Draw(Output*) const;
	virtual Point GetCenter() const;
	virtual bool Rotate(Output* pOut, int) ;	//Rotate the figure
	virtual bool Resize(Output* pOut, float Ratio);	//Resize the figure
	virtual bool Move(Output*, double, double);		//Move the figure
	virtual bool CheckCoordinates(double, double);
	virtual void RandomCoordinates(Output* pOut);
	virtual void ResizeHalfLeft();
	double sign(Point p1, Point p2, Point p3); //Function used in CheckCoordinates functions
	virtual void Save(ofstream &OutFile, Output* pOut) ;	//Save the figure parameters to the file
	virtual void Load(ifstream &InFile, Output* pOut) ;	//Load the figure parameters to the file
	virtual TYPE GetType();	//returns the type of the figure
	virtual double GetArea();	//returns the area of the figure

	virtual void PrintInfo(Output* pOut) ;	//print all figure info on the status bar

	virtual CFigure* Copy(bool);	//create an object with the same info of the old one
	~CTriangle();
};

