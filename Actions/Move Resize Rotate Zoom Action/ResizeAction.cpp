#include "ResizeAction.h"
#include "..\..\Figures\CRectangle.h"
#include "..\..\ApplicationManager.h"


ResizeAction::ResizeAction(ApplicationManager * pApp) :Action(pApp) { Ratio = 1; }

void ResizeAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->CreateResizeBar();
	pOut->PrintMessage("Choose the ratio to Resize by ");
	ActType = pIn->GetUserAction(RESIZEBAR);
	switch (ActType)
	{

	case RESIZEBY1_4:
		Ratio = 0.25;
		break;
	case RESIZEBY1_2:
		Ratio = 0.5;
		break;
	case RESIZEBY2:
		Ratio = 2;
		break;
	case RESIZEBY4:
		Ratio = 4;
		break;
	default:
		break;
	}
}

bool ResizeAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Resize");
		return false;
	}
	else
	{
		ReadActionParameters();
		if (Ratio == 1) 
		{
			ActionSelected = &ActType;
			pManager->UpdateInterface();
			pManager->GetOutput()->ClearStatusBar();
			return false;
		}
		if (pManager->ResizeAll(Ratio))
		{
			pManager->GetOutput()->PrintMessage("Resize Action by " + to_string(Ratio) +"for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
			return true;
		}
		else
		{
			pManager->GetOutput()->PrintMessage("Error : Out of Boundaries");
			return false;
		}
	}

}

void ResizeAction::Undo()
{
	Action::Undo();
	pManager->ResizeAll(1 / Ratio);
	pManager->GetOutput()->PrintMessage("Undo Resize Action by " + to_string(Ratio) + "for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
}

void  ResizeAction::Redo()
{
	Action::Undo();
	pManager->ResizeAll(Ratio);
	pManager->GetOutput()->PrintMessage("Redo Resize Action by " + to_string(Ratio) + "for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");

}

ResizeAction::~ResizeAction()
{ }