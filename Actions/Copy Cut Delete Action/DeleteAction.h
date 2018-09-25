#pragma once
#include "..\Action.h"
#include "..\..\Figures\CFigure.h"

class DeleteAction :public Action
{
	CFigure**DeletedList;
	int*indexInList;
public:

	DeleteAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~DeleteAction();

};

