#include "AddRectAction.h"
#include "..\..\Figures\CRectangle.h"

#include "..\..\ApplicationManager.h"


AddRectAction::AddRectAction(ApplicationManager * pApp):Action(pApp)
{}

void AddRectAction::ReadActionParameters() 
{	
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Rectangle: Click at first corner");
	
	//Read 1st corner and store in point P1
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P1 = pIn->GetLastPoint();

	pOut->PrintMessage("New Rectangle: Click at second corner");

	//Read 2nd corner and store in point P2
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P2 = pIn->GetLastPoint();

	pManager->AxesTransition(P1);
	pManager->AxesTransition(P2);

	if (pOut->isFilled()) RectGfxInfo.isFilled = true;
	else RectGfxInfo.isFilled = false;

	//get drawing, filling colors and pen width from the interface
	RectGfxInfo.DrawClr = pOut->getCrntDrawColor();
	RectGfxInfo.FillClr = pOut->getCrntFillColor();
	RectGfxInfo.BorderWdth = (pOut->getCrntPenWidth());

	pOut->ClearStatusBar();

}

//Execute the action
bool AddRectAction::Execute(ActionType *&ActionSelected)
{
	//This action needs to read some parameters first
	ReadActionParameters();

	if (ActType != DRAWING_AREA)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}
	
	//Create a rectangle with the parameters read from the user
	CRectangle *R=new CRectangle(P1, P2, RectGfxInfo);

	ID = R->GetID();

	//Add the rectangle to the list of figures
	pManager->AddFigure(R);


	return true;
}

void AddRectAction::Undo()
{
	Selected = pManager->FigIsSelected(ID);
	pManager->DeleteLastFig();
	pManager->GetOutput()->PrintMessage("Undo Drawing Rectangle");
}

void  AddRectAction::Redo()
{
	CRectangle *R = new CRectangle(P1, P2, RectGfxInfo, ID);
	R->SetSelected(Selected);
	pManager->AddFigure(R);
	pManager->GetOutput()->PrintMessage("Redo Drawing Rectangle");
}

AddRectAction::~AddRectAction()
{ }
