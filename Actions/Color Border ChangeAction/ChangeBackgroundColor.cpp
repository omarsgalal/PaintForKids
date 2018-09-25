#include "ChangeBackgroundColor.h"


ChangeBackgroundColor::ChangeBackgroundColor(ApplicationManager *pApp) :Action(pApp)
{ }

void ChangeBackgroundColor::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Changing Background Color : Choose the new Color ");
	pOut->CreateColorBar();
	BKGrndColor = pIn->getColor();
	pOut->ClearStatusBar();
}

bool ChangeBackgroundColor::Execute(ActionType *&ActionSelected)
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (BKGrndColor == NULL)
		return false;
	PreviousBKGrndColor = pOut->getBkgroundColor();
	pOut->SetCrntBkgroundColor(*BKGrndColor);
	return true;
}

void ChangeBackgroundColor::Undo()
{
	Output* pOut = pManager->GetOutput();
	pOut->SetCrntBkgroundColor(PreviousBKGrndColor);
	pManager->GetOutput()->PrintMessage("Undo Changing Background Color");
}

void  ChangeBackgroundColor::Redo()
{
	Output* pOut = pManager->GetOutput();
	pOut->SetCrntBkgroundColor(*BKGrndColor);
	pManager->GetOutput()->PrintMessage("Redo Changing Background Color");
}

ChangeBackgroundColor::~ChangeBackgroundColor()
{ }
