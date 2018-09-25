#include "CutAction.h"
#include "..\..\ApplicationManager.h"


CutAction::CutAction(ApplicationManager * pApp) :Action(pApp)
{
	CutList = NULL;
	indexInList = NULL;
}

void CutAction::ReadActionParameters()
{}

bool CutAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Cut");
		return false;
	}
	else
	{
		indexInList = pManager->GetIndexList();
		pManager->CutAll(CutList);
		pManager->GetOutput()->PrintMessage("Cut Action for " + to_string(numSelectedFigs) + " Figures is Done Successfully .. Figure(s) Saved to Clipboard");
		return true;
	}
}

void CutAction::Undo()
{ 
	for (int i = 0; i < numSelectedFigs; i++)
	{
		pManager->AddFigure(CutList[i]->Copy(true));
		pManager->AddFigbyIndex(IDlist[i], indexInList[i]);
	}
	Action::Undo();
	pManager->GetOutput()->PrintMessage("Undo Delete Action for " + to_string(numSelectedFigs) + " Figures");
}

void  CutAction::Redo()
{
	for (int i = 0; i < numSelectedFigs; i++)
	{
		delete CutList[i];
	}
	delete[] CutList;
	Action::Redo();
	pManager->CutAll(CutList);
	pManager->GetOutput()->PrintMessage("Redo Delete Action for " + to_string(numSelectedFigs) + " Figures");
}

CutAction::~CutAction()
{
	if (CutList != NULL)
	{
		for (int i = 0; i < numSelectedFigs; i++)
		{
			delete CutList[i];
		}
		delete[] CutList;
		delete[] indexInList;
	}
}
