#include "SendBackAction.h"

#include "..\..\ApplicationManager.h"



SendBackAction::SendBackAction(ApplicationManager *pApp) : Action(pApp)
{ }

void SendBackAction::ReadActionParameters()
{ }


bool SendBackAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to SendBack");
		return false;
	}
	else
	{
		indexInList = pManager->GetIndexList();
		pManager->SendBackAll();
		pManager->GetOutput()->PrintMessage("SendBack Action for " + to_string(numSelectedFigs) + " Figures is Done Succussfully");
		return true;
	}
}

void SendBackAction::Undo()
{
	Action::Undo();
	for (int i = 0; i < numSelectedFigs; i++)
	{
		pManager->AddFigbyIndex(IDlist[i], indexInList[i]);
	}
	pManager->GetOutput()->PrintMessage("Undo SendBack Action for " + to_string(numSelectedFigs) + " Figures");
}

void SendBackAction::Redo()
{
	Action::Redo();
	pManager->SendBackAll();
	pManager->GetOutput()->PrintMessage("Redo SendBack Action for " + to_string(numSelectedFigs) + " Figures");
}


SendBackAction::~SendBackAction()
{
	if (numSelectedFigs != 0)
		delete[]indexInList;
}