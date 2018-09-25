#pragma once
#include "..\Action.h"

class RedoAction :public Action
{
public:
	RedoAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~RedoAction();
};

