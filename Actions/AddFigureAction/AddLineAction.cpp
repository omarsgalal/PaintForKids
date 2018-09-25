#include "AddLineAction.h"
#include "..\..\Figures\CLine.h"
#include "..\..\ApplicationManager.h"


AddLineAction::AddLineAction(ApplicationManager *pApp)
	:Action(pApp)
{ }

void AddLineAction::ReadActionParameters() {

	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Line: Click the first Point ");
	//Get the first point of the line
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P1 = pIn->GetLastPoint();

	pOut->PrintMessage("New Line: Click the second Point");
	//Get the second point of the line
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA) return;
	P2 = pIn->GetLastPoint();

	pManager->AxesTransition(P1);
	pManager->AxesTransition(P2);

	if (pOut->isFilled()) LineGfxInfo.isFilled = true;
	else LineGfxInfo.isFilled = false;
	//get drawing, filling colors and pen width from the interface
	LineGfxInfo.DrawClr = pOut->getCrntDrawColor();
	LineGfxInfo.BorderWdth = (pOut->getCrntPenWidth());
	LineGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();
}
bool AddLineAction::Execute(ActionType *&ActionSelected)
{

	//This action needs to read some parameters first
	ReadActionParameters();

	if (ActType != DRAWING_AREA)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}

	//Create a Line with the parameters read from the user

	CFigure *L = new CLine(P1, P2, LineGfxInfo);

	ID = L->GetID();

	//Add a Line to the list of figuers 
	pManager->AddFigure(L);

	return true;
}

void AddLineAction::Undo()
{
	Selected = pManager->FigIsSelected(ID);
	pManager->DeleteLastFig();
	pManager->GetOutput()->PrintMessage("Undo Drawing Line");
}

void  AddLineAction::Redo()
{
	//Create a Line with the parameters read from the user

	CFigure *L = new CLine(P1, P2, LineGfxInfo, ID);

	L->SetSelected(Selected);

	//Add a Line to the list of figuers 
	pManager->AddFigure(L);

	pManager->GetOutput()->PrintMessage("Redo Drawing Line");
}

AddLineAction::~AddLineAction()
{ }
