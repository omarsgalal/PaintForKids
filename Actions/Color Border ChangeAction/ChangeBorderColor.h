#pragma once
#ifndef CHNGBORDER_ACTION_H
#define CHNGBORDER_ACTION_H

#include "..\Action.h"

class ChangeBorderColor : public Action
{
	color*BorderColor, LastBorderColor;
	color* FigsBorderColors;
public:
	ChangeBorderColor(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~ChangeBorderColor();
};
#endif	

