#ifndef INPUT_H
#define INPUT_H

#include "..\DEFS.h"
#include "UI_Info.h" 
#include "..\CMUgraphicsLib\CMUgraphics.h"

class Output;

class Input		//The application manager should have a pointer to this class
{
private:
	window *pWind;	//Pointer to the Graphics Window
public:
	Input(window *pW);		//Consturctor

	void GetPointClicked(double &x, double &y) const;//Get coordinate where user clicks

	string GetSrting(Output* pO) const;	 //Returns a string entered by the user

	ActionType GetUserAction(BarType ) const; //Read the user click and map to an action

	ActionType GetExitAction()const; //Read the user click and map to one of Save or don't save or exit

	color* getColor() const;		// returns the color from the color 

	int getBorderWidth(Output *pO) const;		//returns the border width of the shape taken from the user

	Point GetLastPoint()const;


	~Input();
};

#endif