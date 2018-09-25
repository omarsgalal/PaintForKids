#pragma once
#include "..\..\Action.h"
#include "..\..\..\Figures\CFigure.h"

class PickByTypeFill : public Action
{
	bool Found, Filled, TemporaryFilled;
	TYPE T, TemporaryT;
	int Valid, InValid, Count;
	float Grade;
	color FillColor, TemporaryFillColor;
	Point P;
	int ID;
public:
	PickByTypeFill(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);
	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~PickByTypeFill();
};

