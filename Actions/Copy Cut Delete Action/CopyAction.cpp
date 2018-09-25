#include "CopyAction.h"

#include"..\..\ApplicationManager.h"

CopyAction::CopyAction(ApplicationManager* pApp):Action(pApp)
{ }

void CopyAction::ReadActionParameters()
{ }


bool CopyAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Copy");
		return false;
	}
	else
	{
		pManager->CopyAll();
		pManager->GetOutput()->PrintMessage("Copy Action for " + to_string(numSelectedFigs) +" Figures is Done Successfully .. Figure(s) Saved to Clipboard");
		return true;
	}
}

void CopyAction::Undo()
{ }

void  CopyAction::Redo()
{ }

CopyAction::~CopyAction()
{ }