#ifndef RESIZE_ACTION_H
#define RESIZE_ACTION_H

#include "..\Action.h"
#include "..\..\ApplicationManager.h"

class ResizeAction : public Action
{
	float Ratio;
public:
	ResizeAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~ResizeAction();

};
#endif	