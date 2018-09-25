#include "AddCircleAction.h"
#include "..\..\Figures\CCircle.h"
#include"..\..\ApplicationManager.h"


AddCircleAction::AddCircleAction(ApplicationManager *pApp) :Action(pApp)
{ }

void AddCircleAction::ReadActionParameters()
{

	//Get a Pointer to the Input / Output Interfaces
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput(); 

	//Read 1st Point and store in point P1
	pOut->PrintMessage("New Circle: Click the Center Point");
	ActType = pManager->GetUserAction();
	
	if (ActType != DRAWING_AREA) return;
	P1 = pIn->GetLastPoint();

	//Read 2nd Point and store in point P2
	pOut->PrintMessage("New Circle: Click the Second Point"); 
	ActType = pManager->GetUserAction();

	if (ActType != DRAWING_AREA) return;
	P2 = pIn->GetLastPoint();

	pManager->AxesTransition(P1);
	pManager->AxesTransition(P2);
		
	if (pOut->isFilled()) CircGfxInfo.isFilled = true;
	else CircGfxInfo.isFilled = false;

	//get drawing, filling colors and pen width from the interface
	CircGfxInfo.DrawClr = pOut->getCrntDrawColor();
	CircGfxInfo.FillClr = pOut->getCrntFillColor();
	CircGfxInfo.BorderWdth = (pOut->getCrntPenWidth());

	pOut->ClearStatusBar();

}

bool AddCircleAction::Execute(ActionType *&ActionSelected)
{
	//This action needs to read some parameters first
	ReadActionParameters(); 

	if (ActType != DRAWING_AREA)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}
	radius = sqrt(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));

	CCircle *C = new CCircle(P1,radius, CircGfxInfo);

	if (C->CheckInBoundries(pManager->GetOutput(), { P1.x - radius , P1.y - radius }, { P1.x + radius , P1.y + radius }))
	{
		//Add the Circle to the list of figures
		pManager->AddFigure(C);
		ID = C->GetID();
		return true;
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Error : Out of Boundaries");
		delete C;
		return false;
	}

}

void AddCircleAction::Undo()
{
	Selected = pManager->FigIsSelected(ID);
	pManager->DeleteLastFig();
	pManager->GetOutput()->PrintMessage("Undo Drawing Circle");
}

void  AddCircleAction::Redo()
{
	CCircle *C = new CCircle(P1, radius, CircGfxInfo, ID);
	C->SetSelected(Selected);
	pManager->AddFigure(C);
	pManager->GetOutput()->PrintMessage("Redo Drawing Circle");
}

AddCircleAction::~AddCircleAction()
{ }
