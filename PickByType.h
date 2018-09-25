#pragma once
#include "Actions\Action.h"
#include "Figures\CFigure.h"
class PickByType :
	public Action
{
	TYPE T,TemporaryT ;
	int Valid, InValid,Count,Grade;

public:
	PickByType(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual bool Execute();
	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();
	~PickByType();
};

