#include "BringFrontAction.h"
#include "..\..\ApplicationManager.h"



BringFrontAction::BringFrontAction(ApplicationManager* pApp) :Action(pApp)
{ }


void BringFrontAction::ReadActionParameters()
{ }

bool BringFrontAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to BringFront");
		return false;
	}
	else
	{
		indexInList = pManager->GetIndexList();
		pManager->BringFrontAll();
		pManager->GetOutput()->PrintMessage("BringFront Action for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
		return true;
	}
}

void BringFrontAction::Undo()
{
	Action::Undo();
	for (int i = 0; i < numSelectedFigs; i++)
	{
		pManager->AddFigbyIndex(IDlist[i], indexInList[i]);
	}
	pManager->GetOutput()->PrintMessage("Undo BringFront Action for " + to_string(numSelectedFigs) + " Figures");
}

void  BringFrontAction::Redo()
{
	Action::Redo();
	pManager->BringFrontAll();
	pManager->GetOutput()->PrintMessage("Redo BringFront Action for " + to_string(numSelectedFigs) + " Figures");
}

BringFrontAction::~BringFrontAction()
{
	if (numSelectedFigs != 0)
		delete[] indexInList;
}

