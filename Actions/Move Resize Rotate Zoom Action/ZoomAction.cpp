#include "ZoomAction.h"

#include "..\..\ApplicationManager.h"


ZoomAction::ZoomAction(ApplicationManager * pApp) :Action(pApp) { ZoomFactor = -1; }

void ZoomAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->CreateZoomBar();
	pOut->PrintMessage("Choose the Zoom Factor");
	ActType = pIn->GetUserAction(ZOOMBAR);
	switch (ActType)
	{
	case ZOOMIN:
		ZoomFactor = 2;
		pOut->SetZoomFactor((int)(pOut->GetZoomFactor()*ZoomFactor));
		pOut->PrintMessage("Zoom in is selected");
		break;
	case ZOOMOUT:
		ZoomFactor = 0.5;
		pOut->SetZoomFactor((int)(pOut->GetZoomFactor()*ZoomFactor));
		pOut->PrintMessage("Zoom out is selected");
		break;
	}
}

bool ZoomAction::Execute(ActionType *&ActionSelected)
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (ZoomFactor == -1)
	{
		ActionSelected = &ActType;
		pManager->UpdateInterface();
		pOut->ClearStatusBar();
		return false;
	}
	if (pOut->GetZoomFactor() < 1)
	{
		pOut->ClearStatusBar();
		pOut->SetZoomFactor(1);
		return false;
	}
	return true;
}


ZoomAction::~ZoomAction()
{ }