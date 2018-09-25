#ifndef CRECT_H
#define CRECT_H

#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	
	Point Corner2;
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo ,int id = 0);
	CRectangle();
	virtual void Draw(Output* pOut) const;
	virtual Point GetCenter() const;
	virtual bool Move(Output*, double, double);
	virtual bool Resize(Output* pOut, float Ratio);	//Resize the figure
	virtual bool Rotate(Output*, int);
	virtual void PrintInfo(Output* pOut);
	virtual bool CheckCoordinates(double, double);
	virtual void RandomCoordinates(Output* pOut);
	virtual void ResizeHalfLeft();
	virtual void Save(ofstream &OutFile, Output* pOut);
	virtual void Load(ifstream &InFile, Output* pOut);
	virtual CFigure* Copy(bool);	//create an object with the same info of the old one
	virtual TYPE GetType();	//returns the type of the figure
	virtual double GetArea();	//returns the area of the figure

};

#endif