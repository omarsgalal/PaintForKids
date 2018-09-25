#include "PickByColor.h"

#include "..\..\..\ApplicationManager.h"



PickByColor::PickByColor(ApplicationManager* pApp) :Action(pApp)
{
	Valid = InValid = Count = 0;
	Found = Filled = false;
	ID = -1;
}

void PickByColor::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	//bool S = false;
	if (Found)
	{
		do
		{
			ActType = pManager->GetUserAction();
			if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
				return;
			P = pIn->GetLastPoint();
			ID = pManager->GetFigIdByPoint(P.x, P.y);
		} while (ID == -1);
		
		TemporaryFilled = pManager->FigIsFilled(ID);
		if (TemporaryFilled)
		{
			TemporaryFillColor = pManager->GetFigFillColorByID(ID);
		}
	}
	else
	{
		do
		{
			ActType = pManager->GetUserAction();
			if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
				return;
			P = pIn->GetLastPoint();
			ID = pManager->GetFigIdByPoint(P.x, P.y);
		} while (ID == -1);

		TemporaryFilled = Filled = pManager->FigIsFilled(ID);
		if (Filled)
			TemporaryFillColor = FillColor = pManager->GetFigFillColorByID(ID);
		Count = pManager->GetFillColorCount(FillColor, Filled);
		Found = true;
	}
}

bool PickByColor::Execute(ActionType *&ActionSelected)
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	do
	{
		ReadActionParameters();
		if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
		{
			pManager->GetOutput()->ClearStatusBar();
			ActionSelected = &ActType;
			return false;
		}

		if ((Filled && TemporaryFilled && TemporaryFillColor == FillColor) || (!Filled && !TemporaryFilled))
		{
			Valid++; Count--;
			pManager->DeleteFigByID(ID);
			pManager->UpdateInterface();
			pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid));

		}
		else
		{
			InValid++;
			pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid));
		}
	}
	while (Count != 0);

	Grade = ((float)Valid / (Valid + InValid)) * 100;

	pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid) + "\tyour grade = " + to_string(Grade) + "%");
	return true;
}

PickByColor::~PickByColor()
{ }

void PickByColor::Undo()
{ }

void PickByColor::Redo()
{ }
