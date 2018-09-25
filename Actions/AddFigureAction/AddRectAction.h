#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H

#include "..\Action.h"

//Add Rectangle Action class
class AddRectAction: public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	int ID;
	bool Selected;
public:
	AddRectAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual bool Execute(ActionType *&) ;

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
	
	virtual ~AddRectAction();
};

#endif