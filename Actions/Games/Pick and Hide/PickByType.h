#pragma once
#include "..\..\Action.h"
#include "..\..\..\Figures\CFigure.h"

class PickByType : public Action
{
	TYPE T, TemporaryT;
	int Valid, InValid, Count, ID;
	float  Grade;
	Point P;

public:
	PickByType(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~PickByType();
};

