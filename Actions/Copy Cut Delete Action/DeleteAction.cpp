#include "DeleteAction.h"
#include "..\..\ApplicationManager.h"


DeleteAction::DeleteAction(ApplicationManager * pApp) :Action(pApp)
{ }

void DeleteAction::ReadActionParameters()
{ }

bool DeleteAction::Execute(ActionType *&ActionSelected)
{
	if (numSelectedFigs == 0)
	{
		pManager->GetOutput()->PrintMessage("No Figure is Selected to Delete");
		return false;
	}
	else
	{
		indexInList = pManager->GetIndexList();
		pManager->DeleteAll(DeletedList);
		pManager->GetOutput()->PrintMessage("Delete Action for " + to_string(numSelectedFigs) + " Figures is Done Successfully");
		return true;
	}
}

void DeleteAction::Undo()
{
	for (int i = 0; i < numSelectedFigs; i++)
	{
		pManager->AddFigure(DeletedList[i]);
		pManager->AddFigbyIndex(IDlist[i], indexInList[i]);
	}
	Action::Undo();
	delete[] DeletedList;
	pManager->GetOutput()->PrintMessage("Undo Delete Action for " + to_string(numSelectedFigs) + " Figures");
}

void  DeleteAction::Redo()
{
	Action::Redo();
	pManager->DeleteAll(DeletedList);
	pManager->GetOutput()->PrintMessage("Redo Delete Action for " + to_string(numSelectedFigs) + " Figures");
}


DeleteAction::~DeleteAction()
{
	for (int i = 0; i < numSelectedFigs; i++)
		delete DeletedList[i];
	if (numSelectedFigs != 0)
		delete[] indexInList;
}