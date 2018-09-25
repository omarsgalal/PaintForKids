#ifndef ADD_TRIANGLE_H
#define ADD_TRIANGLE_H

#include "..\Action.h"

class AddTriAction : public Action
{
private:
	Point P1, P2, P3; //Circle Points
	int ID;
	bool Selected;

	GfxInfo TrianGfxInfo;
public:
	AddTriAction(ApplicationManager *pApp);

	//Read Triangle Parameters 
	virtual void ReadActionParameters();

	//Add Circle to the ApplicationManager
	virtual bool Execute(ActionType *&);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual ~AddTriAction();
};
#endif // !ADD_TRIANGLE_H

