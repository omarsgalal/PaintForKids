#pragma once
#ifndef CHNGBKGRND_ACTION_H
#define CHNGBKGRND_ACTION_H

#include "..\Action.h"
#include"..\..\ApplicationManager.h"

class ChangeBackgroundColor : public Action
{
	color*BKGrndColor;
	color PreviousBKGrndColor;
public:
	ChangeBackgroundColor(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~ChangeBackgroundColor();
};
#endif	
