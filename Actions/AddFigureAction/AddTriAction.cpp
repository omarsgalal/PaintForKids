#include "AddTriAction.h"
#include "..\..\Figures\CTriangle.h"
#include "..\..\ApplicationManager.h"
#include "..\..\GUI\input.h"
#include "..\..\GUI\Output.h"

AddTriAction::AddTriAction(ApplicationManager *pApp)
	:Action(pApp)
{ }

void AddTriAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output *pOut = pManager->GetOutput();
	Input *pIn = pManager->GetInput();

	//Read 1st Point and store in point P1
	pOut->PrintMessage("New Triangle: Click the First Point");
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P1 = pIn->GetLastPoint();

	//Read 2nd Point and store in point P2
	pOut->PrintMessage("New Triangle: Click the Second Point");
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P2 = pIn->GetLastPoint();

	//Read 3rd Point and store in Point P3
	pOut->PrintMessage("New Triangle: Click the third Point");
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P3 = pIn->GetLastPoint();

	pManager->AxesTransition(P1);
	pManager->AxesTransition(P2);
	pManager->AxesTransition(P3);

	if (pOut->isFilled()) TrianGfxInfo.isFilled = true;
	else TrianGfxInfo.isFilled = false;

	//get drawing, filling colors and pen width from the interface
	TrianGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TrianGfxInfo.FillClr = pOut->getCrntFillColor();
	TrianGfxInfo.BorderWdth = (pOut->getCrntPenWidth());

	pOut->ClearStatusBar();
}

bool AddTriAction::Execute(ActionType *&ActionSelected)
{
	//This action needs to read some parameters first
	ReadActionParameters();

	if (ActType != DRAWING_AREA)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}

	//Create a  with the parameters read from the user
	CTriangle *T = new CTriangle(P1, P2, P3, TrianGfxInfo);
	ID = T->GetID();
	//Add the Triangle  to the list of figures
	pManager->AddFigure(T);

	return true;

}

void AddTriAction::Undo()
{
	Selected = pManager->FigIsSelected(ID);
	pManager->DeleteLastFig();
	pManager->GetOutput()->PrintMessage("Undo Drawing Triangle");
}

void  AddTriAction::Redo()
{
	CTriangle *T = new CTriangle(P1, P2, P3, TrianGfxInfo, ID);
	T->SetSelected(Selected);
	pManager->AddFigure(T);
	pManager->GetOutput()->PrintMessage("Redo Drawing Triangle");
}

AddTriAction::~AddTriAction()
{ }
