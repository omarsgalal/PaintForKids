#ifndef ACTION_H
#define ACTION_H

#include "..\DEFS.h"

class ApplicationManager; //forward class declaration


//Base class for all possible actions
class Action
{
protected:
	ApplicationManager *pManager;	//Actions needs AppMngr to do their job
	int* IDlist;	//contains the ids of selected figures
	int numSelectedFigs;	//the number of selected figures
	ActionType ActType;
public:

	Action(ApplicationManager *pApp);	//constructor

	virtual ~Action();	//destructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() =0;
	
	//Execute action (code depends on action type)
	virtual bool Execute(ActionType *&ActionSelected)=0;

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();

};

#endif