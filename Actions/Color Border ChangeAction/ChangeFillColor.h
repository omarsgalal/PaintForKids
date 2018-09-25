#pragma once
#ifndef CHNGFill_ACTION_H
#define CHNGFill_ACTION_H

#include "..\Action.h"

class ChangeFillColor : public Action
{
	color*fillcolor, lastFillColor;
	color* Figscolors;
	bool* wasFilled, defFilled;
public:
	ChangeFillColor(ApplicationManager *pApp);

	virtual ~ChangeFillColor();

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType*&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

};
#endif	

