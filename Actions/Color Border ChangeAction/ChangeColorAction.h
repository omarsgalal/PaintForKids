#pragma once
#include "..\Action.h"

class ChangeColorAction : public Action
{
	Action*ChangeColorType;
public:
	ChangeColorAction(ApplicationManager*pApp);

	void ReadActionParameters();

	bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~ChangeColorAction();

};

