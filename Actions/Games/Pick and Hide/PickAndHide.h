#pragma once
#include "..\..\Action.h"

class PickAndHide : public Action
{
	Action* PickMode;
public:
	PickAndHide(ApplicationManager* pApp);

	virtual ~PickAndHide();

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);
	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

