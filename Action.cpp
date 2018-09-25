#include "Actions\Action.h"
#include "ApplicationManager.h"


Action::Action(ApplicationManager *pApp)
{
	pManager = pApp;
	IDlist = pManager->GetIDList(numSelectedFigs);
}


void Action::Undo()
{
	pManager->UnselectAll();
	pManager->SelectFigsByID(IDlist, numSelectedFigs);
}

void Action::Redo()
{
	pManager->UnselectAll();
	pManager->SelectFigsByID(IDlist, numSelectedFigs);
}

Action::~Action()
{
	if (numSelectedFigs != 0)
		delete[] IDlist;
}