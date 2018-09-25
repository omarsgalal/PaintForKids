#include "UndoAction.h"
#include "..\..\ApplicationManager.h"


UndoAction::UndoAction(ApplicationManager* pApp): Action(pApp)
{ }


void UndoAction::ReadActionParameters()
{ }


bool UndoAction::Execute(ActionType *&ActionSelected)
{
	Action* Act = pManager->UndoLastAction();
	if (Act != NULL)
		Act->Undo();
	return false;
}

void UndoAction::Undo()
{

}

void  UndoAction::Redo()
{

}


UndoAction::~UndoAction()
{
}
