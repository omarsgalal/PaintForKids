#include "RotateAction.h"

#include "..\..\ApplicationManager.h"


RotateAction::RotateAction(ApplicationManager* pApp): Action(pApp)
{
	degrees = 0;
}


void RotateAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	
	pOut->CreateRotateBar();
	pOut->PrintMessage("Choose the degrees to Resize by ");
	ActType  = pIn->GetUserAction(ROTATEBAR);
	switch (ActType)
	{
	case ROTATEBY90:
		degrees = 90;
		break;
	case ROTATEBY180:
		degrees = 180;
		break;
	case ROTATEBY270:
		degrees = 270;
		break;
	default:
		break;
	}
}


bool RotateAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Rotate");
		return false;
	}
	else
	{
		ReadActionParameters();
		if (degrees == 0)
		{
			ActionSelected = &ActType;
			pManager->UpdateInterface();
			pManager->GetOutput()->ClearStatusBar();
			return false;
		}
		if (pManager->RotateAll(degrees))
		{
			pManager->GetOutput()->PrintMessage("Rotate Action by " + to_string(degrees) + "for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
			return true;
		}
		else
		{
			pManager->GetOutput()->PrintMessage("Error : Out of Boundaries ");
			return false;
		}
	}

}

void RotateAction::Undo()
{
	Action::Undo();
	pManager->RotateAll(360-degrees);
	pManager->GetOutput()->PrintMessage("Undo Rotate Action by " + to_string(degrees) + "for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
}

void  RotateAction::Redo()
{
	pManager->RotateAll(degrees);
	pManager->GetOutput()->PrintMessage("Redo Rotate Action by " + to_string(degrees) + "for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
}


RotateAction::~RotateAction()
{
}