#include "RedoAction.h"
#include "..\..\ApplicationManager.h"


RedoAction::RedoAction(ApplicationManager *pApp):Action(pApp)
{
}



void RedoAction::ReadActionParameters()
{

}


bool RedoAction::Execute(ActionType *&ActionSelected)
{
	Action* Act = pManager->RedoLastAction();
	if (Act != NULL)
		Act->Redo();
	return false;
}

void RedoAction::Undo()
{

}

void  RedoAction::Redo()
{

}


RedoAction::~RedoAction()
{
}
