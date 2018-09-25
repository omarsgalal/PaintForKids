#include "PasteAction.h"

#include "..\..\ApplicationManager.h"


PasteAction::PasteAction(ApplicationManager* pApp) :Action(pApp)
{
	Size = pManager->GetClipboardSize();
	PastedFigures = new CFigure*[Size];
}


void PasteAction::ReadActionParameters()
{
	pManager->GetOutput()->PrintMessage("Click anywhere to paste figure(s)");

	ActType = pManager->GetUserAction();

	if (ActType != DRAWING_AREA) return;

	P = pManager->GetInput()->GetLastPoint();

	pManager->AxesTransition(P);
}


bool PasteAction::Execute(ActionType *&ActionSelected)
{
	if (!pManager->CheckClipboard())
	{
		pManager->GetOutput()->PrintMessage("Cannot Paste : Clipboard is Empty");
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

		if (pManager->PasteAll(P, X_diff, Y_diff, PastedFigures))
		{
			pManager->GetOutput()->PrintMessage("Paste Action for " + to_string(Size) + " Figures is Done Successfully");
			return true;
		}
		else
		{
			pManager->GetOutput()->PrintMessage("Error : Out of Boundaries ");
			return false;
		}
	}
}

void PasteAction::Undo()
{
	Action::Undo();
	for (int i = 0; i < Size; i++)
	{
		pManager->DeleteLastFig();
	}
	pManager->GetOutput()->PrintMessage("Undo Paste Action for " + to_string(Size) + " Figures");
}

void  PasteAction::Redo()
{
	Action::Redo();
	for (int i = 0; i < Size; i++)
	{
		pManager->AddFigure(PastedFigures[i]);
	}
	pManager->GetOutput()->PrintMessage("Redo Paste Action for " + to_string(Size) + " Figures");
}


PasteAction::~PasteAction()
{
	for (int i = 0; i < Size; i++)
	{
		delete PastedFigures[i];
	}
	if (Size != 0)
		delete[] PastedFigures;
}