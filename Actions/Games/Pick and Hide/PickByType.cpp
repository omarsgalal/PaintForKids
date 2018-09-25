#include "PickByType.h"

#include "..\..\..\ApplicationManager.h"



PickByType::PickByType(ApplicationManager* pApp) :Action(pApp)
{
	Valid = InValid = Count = 0;
	T = TemporaryT = TYPE(-1);
}

void PickByType::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ActType = pManager->GetUserAction();

	if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
		return;

	P = pIn->GetLastPoint();

	TemporaryT = pManager->GetFigureType(P.x, P.y);
}

bool PickByType::Execute(ActionType *&ActionSelected)
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	while (T == TYPE(-1))
	{
		ActType = pManager->GetUserAction();

		if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
		{
			pManager->GetOutput()->ClearStatusBar();
			ActionSelected = &ActType;
			return false;
		}

		P = pIn->GetLastPoint();

		T = pManager->GetFigureType(P.x, P.y);

		TemporaryT = T;
	}
	ID = pManager->GetFigIdByPoint(P.x, P.y);
	pManager->DeleteFigByID(ID);
	pManager->UpdateInterface();
	Count--; Valid++;

	string Output;
	switch (T)
	{
	case TRECTANGLE:
		Output = "Select All RECTANGLES ";
		break;
	case TCIRCLE:
		Output = "Select All CIRCLES ";
		break;
	case TTRIANGLE:
		Output = "Select All TRIANGLES ";
		break;
	case TLINE:
		Output = "Select All LINES ";
		break;
	}
	Count = pManager->GetTypeCount(T);
	pManager->GetOutput()->PrintMessage(Output + " : Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid));

	//if (Count == 1) ActType = STATUS;

	while (Count != 0 && ( ActType == DRAWING_AREA || ActType == STATUS || ActType == EMPTY ))
	{
		ReadActionParameters();
		if (TemporaryT == T)
		{
			Valid++; Count--;
			ID = pManager->GetFigIdByPoint(P.x, P.y);
			pManager->DeleteFigByID(ID);
			pManager->UpdateInterface();
			pManager->GetOutput()->PrintMessage(Output + " : Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid));

		}
		else
		{
			if (TemporaryT != -1 )
				InValid++;
			pManager->GetOutput()->PrintMessage(Output + " : Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid));

		}
	}

	Grade = ((float)Valid / (Valid + InValid)) * 100;
	pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(Valid) + "\t Invalid Picks = " + to_string(InValid) + "\tyour grade = " + to_string(Grade) + "%");
	
	if (ActType != DRAWING_AREA)
	{
		pManager->GetOutput()->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}
	return true;
}

PickByType::~PickByType()
{
}

void PickByType::Undo()
{}

void PickByType::Redo() {}
