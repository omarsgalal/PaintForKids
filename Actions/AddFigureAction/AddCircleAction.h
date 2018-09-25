#ifndef ADD_CIRCLE_H
#define ADD_CIRCLE_H

#include "..\Action.h"

class AddCircleAction : public Action
{
private:
	Point P1, P2; //Circle Points
	double radius;
	GfxInfo CircGfxInfo;
	int ID;
	bool Selected;
public:

	AddCircleAction(ApplicationManager *pApp);

	//Reads Circle Parameters
	virtual void ReadActionParameters();

	//Create Circle and add it to Application Manager
	virtual bool Execute(ActionType *&);

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~AddCircleAction();
};

#endif