#include "PickAndHide.h"
#include "..\..\..\ApplicationManager.h"
#include "PickByArea.h"
#include "PickByColor.h"
#include "PickByType.h"
#include "PickByTypeFill.h"


PickAndHide::PickAndHide(ApplicationManager* pApp):Action(pApp)
{
	PickMode = NULL;
}

PickAndHide::~PickAndHide()
{ }

void PickAndHide::ReadActionParameters()
{
	pManager->GetOutput()->CreatePickAndHideBar();
	ActionType ActType = pManager->GetInput()->GetUserAction(PICKANDHIDEBAR);
	switch (ActType)
	{
	case PICKBYAREA:
		PickMode = new PickByArea(pManager);
		break;
	case PICKBYTYPE:
		PickMode = new PickByType(pManager);
		break;
	case PICKBYFILLCOLOR:
		PickMode = new PickByColor(pManager);
		break;
	case PICKBYTYPEANDFILLCOLOR:
		PickMode = new PickByTypeFill(pManager);
		break;
	}

}

bool PickAndHide::Execute(ActionType *&ActionSelected)
{
	if (pManager->GetFigCount() == 0)
	{
		pManager->GetOutput()->PrintMessage("There are no figures to play !");
		return false;
	}

	ReadActionParameters();
	if (PickMode == NULL)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}
	pManager->ExchangeList(false);
	pManager->UpdateInterface();
	bool executed = PickMode->Execute(ActionSelected);
	pManager->ExchangeList(true);
	return executed;
}

void PickAndHide::Undo()
{ }

void PickAndHide::Redo()
{ }

