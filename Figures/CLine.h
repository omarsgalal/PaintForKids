#pragma once
#include "CFigure.h"
#ifndef CLINE_H
#define CLINE_H

class CLine : public CFigure
{
private:
	Point Start;
	Point End;
public:
	CLine(Point, Point, GfxInfo FigureGfxInfo, int id = 0);
	CLine();
	virtual Point GetCenter() const;
	virtual void Draw(Output* pOut) const;
	virtual bool Rotate(Output*, int); //Rotate the figure
	virtual bool Resize(Output* pOut, float Ratio);	//Resize the figure
	virtual bool Move(Output*, double, double);		//Move the figure
	virtual bool CheckCoordinates(double, double);
	virtual void RandomCoordinates(Output* pOut);
	virtual void ResizeHalfLeft();
	virtual void Save(ofstream &OutFile, Output* pOut); //Save the figure parameters to the file
	virtual void Load(ifstream &Infile, Output* pOut);	//Load the figure parameters to the file
	double LengthOfLine(Point P1, Point P2); //returns the Length of a line given coordinates of two points 
	virtual CFigure* Copy(bool);	//create an object with the same info of the old one
	
	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	virtual TYPE GetType();	//returns the type of the figure
	virtual double GetArea();	//returns the area of the figure

};

#endif
