#pragma once
#include "..\Action.h"
#include"..\..\ApplicationManager.h"

class MoveAction : public Action
{
private:
	Point P;
	double x_diff;
	double y_diff;
	int*indexInList;
public:
	MoveAction(ApplicationManager * pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~MoveAction();
};

