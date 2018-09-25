#include "MoveAction.h"


MoveAction::MoveAction(ApplicationManager * pApp) :Action(pApp)
{ 
	indexInList = NULL;
}

void MoveAction::ReadActionParameters()
{
	pManager->GetOutput()->PrintMessage("Click on point to move Figure(s) to ");

	ActType = pManager->GetUserAction();

	if (ActType != DRAWING_AREA) return;

	P = pManager->GetInput()->GetLastPoint();

	pManager->AxesTransition(P);
}

bool MoveAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Move");
		return false;
	}
	else
	{
		ReadActionParameters();
		if (ActType != DRAWING_AREA)
		{
			pManager->GetOutput()->ClearStatusBar();
			ActionSelected = &ActType;
			return false;
		}
		indexInList = pManager->GetIndexList();
		if (pManager->MoveAll(P, x_diff, y_diff))
		{
			pManager->GetOutput()->PrintMessage("Move Action for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
			return true;
		}
		else
		{
			pManager->GetOutput()->PrintMessage("Error : Out of Boundaries");
			return false;
		}
	}
}

void MoveAction::Undo()
{
	Action::Undo();
	pManager->MoveFigs(-x_diff, -y_diff);
	for (int i = 0; i < numSelectedFigs; i++)
	{
		pManager->AddFigbyIndex(IDlist[i], indexInList[i]);
	}
	pManager->GetOutput()->PrintMessage("Undo Move Action for " + to_string(numSelectedFigs) + " Figures");
}

void  MoveAction::Redo()
{
	Action::Redo();
	pManager->MoveFigs(x_diff, y_diff);
	pManager->BringFrontAll();
	pManager->GetOutput()->PrintMessage("Redo Move Action for " + to_string(numSelectedFigs) + " Figures");
}

MoveAction::~MoveAction()
{
	if (indexInList != NULL)
		delete[] indexInList;
}
