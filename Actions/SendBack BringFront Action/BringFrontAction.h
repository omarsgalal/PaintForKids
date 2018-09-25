#pragma once
#include "..\Action.h"

class BringFrontAction : public Action
{
	int*indexInList;
public:
	BringFrontAction(ApplicationManager* pApp);

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~BringFrontAction();
};

