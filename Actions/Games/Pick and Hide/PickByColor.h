#pragma once
#include "..\..\Action.h"

class PickByColor : public Action
{
	bool Found, Filled, TemporaryFilled;
	int Valid, InValid, Count;
	float Grade;
	color FillColor, TemporaryFillColor;
	Point P;
	int ID;
public:
	PickByColor(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~PickByColor();
};

