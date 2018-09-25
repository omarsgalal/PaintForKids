#pragma once
#include "..\Action.h"
#include "..\..\Figures\CFigure.h"

class PasteAction : public Action
{
	Point P;
	double X_diff, Y_diff;
	CFigure **PastedFigures;
	int Size;
public:
	PasteAction(ApplicationManager* pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~PasteAction();
};