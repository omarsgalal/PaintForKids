#pragma once
#ifndef CHNGBORDERWDTH_ACTION_H
#define CHNGBORDERWDTH_ACTION_H

#include "..\Action.h"

class ChangeBorderWidth : public Action
{
	int previousBorderWidth;
	int BorderWidth;
	int *PreviousBorderWidth;
public:
	ChangeBorderWidth(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~ChangeBorderWidth();
};
#endif	
