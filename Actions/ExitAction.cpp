#include "ExitAction.h"
#include "..\ApplicationManager.h"
#include "..\Actions\Save Load Action\SaveAction.h"

ExitAction::ExitAction(ApplicationManager*pApp) :Action(pApp)
{ }

void ExitAction::ReadActionParameters()
{
	Option = pManager->GetOutput()->CreateExitWindow()->GetExitAction();
}

//Execute action (code depends on action type)
bool ExitAction::Execute(ActionType *&ActionSelected)
{
	if (pManager->GraphisSaved())
		return false;
	ReadActionParameters();
	
	if (Option == SAVE)
	{
		ActionSelected = &Option;
		return false;
	}
	else if (Option == DRAWING_AREA)
		return true;
	else
		return false;
}

//To undo this action 
void ExitAction::Undo()
{ }

//To redo this action
void ExitAction::Redo()
{ }

ExitAction::~ExitAction()
{ }
