#ifndef ADD_LINE_H
#define ADD_LINE_H
#include "..\Action.h"

class AddLineAction :public Action
{
private:
	Point P1, P2;

	GfxInfo LineGfxInfo;

	int ID;

	bool Selected;
public:
	AddLineAction(ApplicationManager * pApp);

	//Reads Line parameters
	virtual void ReadActionParameters();

	//Create Line and send it to Application Manager
	virtual bool Execute(ActionType *&);

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

	virtual ~AddLineAction();
};

#endif

