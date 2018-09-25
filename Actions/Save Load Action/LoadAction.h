#pragma once

#include "..\Action.h"

class LoadAction : public Action
{
private:
	string FileName;
public:
	LoadAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~LoadAction();
};

