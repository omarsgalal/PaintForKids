#pragma once
#include "..\Action.h"


class SaveAction : public Action
{
private:
	string FileName;
public:
	SaveAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~SaveAction();
};

