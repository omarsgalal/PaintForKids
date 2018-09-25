#include "SelectAction.h"

#include "..\..\ApplicationManager.h"

SelectAction::SelectAction(ApplicationManager * pApp) :Action(pApp) { Done = false;  }

void SelectAction::ReadActionParameters()
{

	pManager->GetOutput()->CreateUnselectAllIcon();
	ActType = pManager->GetUserAction();
	Clicked = pManager->GetInput()->GetLastPoint();
	if (ActType != DRAWING_AREA) return;
	pManager->AxesTransition(Clicked);
}

bool SelectAction::Execute(ActionType *&ActionSelected)
{
	Output*pOut = pManager->GetOutput();
	pOut->PrintMessage("Select from figures");
	while (true)
	{
		ReadActionParameters();
		if (ActType != DRAWING_AREA)
		{
			if (Clicked.x > (SELECT + 1)*pOut->GetMenuItemWidth() && Clicked.x < ((SELECT + 2)*pOut->GetMenuItemWidth()) && Clicked.y>0 && Clicked.y < pOut->GetToolBarHeight())
			{
				pManager->UnselectAll();
			}
			else
			{
				pManager->GetOutput()->ClearStatusBar();
				ActionSelected = &ActType;
				Output* pOut = pManager->GetOutput();
				pOut->ClearToolBar();
				pOut->CreateDrawToolBar();
				pOut->ClearStatusBar();
				return true;
			}
		}
		pManager->Select(Clicked.x, Clicked.y);
		pManager->UpdateInterface();
		//ReadActionParameters();
	}
	/*pOut->ClearToolBar();
	pOut->CreateDrawToolBar(); 
	pOut->ClearStatusBar();
	return true;*/
}

void SelectAction::Undo()
{ }

void  SelectAction::Redo()
{ }

SelectAction::~SelectAction()
{ }