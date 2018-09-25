#pragma once
#include "..\Action.h"
#include "..\..\Figures\CFigure.h"

class CutAction:public Action
{
	CFigure**CutList;
	int*indexInList;
public:
	CutAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~CutAction();

};

