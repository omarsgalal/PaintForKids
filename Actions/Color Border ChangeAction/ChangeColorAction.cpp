#include "ChangeColorAction.h"
#include "..\..\ApplicationManager.h"
#include "ChangeBackgroundColor.h"
#include "ChangeBorderColor.h"
#include "ChangeFillColor.h"


ChangeColorAction::ChangeColorAction(ApplicationManager*pApp):Action(pApp)
{
	ChangeColorType = NULL;
}

void ChangeColorAction::ReadActionParameters()
{
	Output*pOut = pManager->GetOutput();
	Input*pIn = pManager->GetInput();

	pOut->CreateChangeClrBar();
	pOut->PrintMessage("Change Color is chosen : Background - Fill - Border ");

	ActType = pIn->GetUserAction(CHANGECOLORBAR);

	switch (ActType)
	{
	case CHANGEBACKGROUNDCOLOR:
		ChangeColorType = new ChangeBackgroundColor(pManager);
		break;
	case CHANGEDRAWCOLOR:
		ChangeColorType = new ChangeBorderColor(pManager);
		break;
	case CHANGEFILLCOLOR:
		ChangeColorType = new ChangeFillColor(pManager);
		break;
	default:
		break;
	}
}

bool ChangeColorAction::Execute(ActionType *&ActionSelected)
{
	ReadActionParameters();
	if (ChangeColorType == NULL)
	{
		ActionSelected = &ActType;
		pManager->GetOutput()->ClearStatusBar();
		pManager->UpdateInterface();
		return false;
	}
	pManager->UpdateInterface();
	return (ChangeColorType->Execute(ActionSelected));
}

void ChangeColorAction::Undo()
{
	ChangeColorType->Undo();
}

void ChangeColorAction::Redo()
{
	ChangeColorType->Redo();
}


ChangeColorAction::~ChangeColorAction()
{
	delete ChangeColorType;
}
