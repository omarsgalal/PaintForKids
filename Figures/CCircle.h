#pragma once
#include "CFigure.h"
#ifndef CCIRCLE_H
#define CCIRCLE_H
#define MYPI 3.141592653589793238462643383279
class CCircle :public CFigure
{
private:
	Point Center;
	double radius;
public:
	CCircle(Point,double, GfxInfo, int id = 0);
	CCircle();

	void Draw(Output* pOut) const; 
	virtual Point GetCenter() const;
	virtual bool Resize(Output*, float) ;	//Resize the figure
	virtual bool Move(Output*, double, double);		//Move the figure
	virtual bool Rotate(Output*, int);
	virtual bool CheckCoordinates(double, double);
	virtual void RandomCoordinates(Output* pOut);
	virtual void ResizeHalfLeft();
	virtual void Save(ofstream &OutFile, Output* pOut);	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile, Output* pOut);	//Load the figure parameters to the file
	
	virtual CFigure* Copy(bool);	//create an object with the same info of the old one
	virtual TYPE GetType();	//returns the type of the figure
	virtual double GetArea();	//returns the area of the figure



	virtual void PrintInfo(Output* pOut);	//print all figure info on the status bar
	~CCircle();
};
#endif
