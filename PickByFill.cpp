#include "PickByFill.h"

#include "ApplicationManager.h"



PickByFill::PickByFill(ApplicationManager* pApp) :Action(pApp)
{
	Valid = InValid = Count = 0;
	Found = Filled = false;
}

void PickByFill::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	double x, y;
	pIn->GetPointClicked(x, y);
	bool S=false;
	if (Found)
	{
		while (!S)
		{
			if (x > 0 && x < UI.width && y>0 && y < UI.height)
				S= pManager->GetFigurecolor(x, y, TemporaryFillColor, TemporaryFilled);
		}
		if (TemporaryFillColor == FillColor|| TemporaryFilled == Filled)
		{
			Count--;
		}

	}
	else {
		while (!Found)
		{
			if (x > 0 && x < UI.width && y>0 && y < UI.height)
				pManager->GetFigurecolor(x, y, FillColor,Filled);
		}
		Count = pManager->GetFillColorCount(FillColor);
		Found = true;
	}
	return;
}

bool PickByFill::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	while (Count != 0)
	{
		ReadActionParameters();
		if (TemporaryFillColor == FillColor)
		{
			Valid++;
		}
		else InValid++;
	}
	Grade = (Valid / (Valid + InValid)) * 100;
	pOut->PrintMessage("Your Final Grade = " + to_string((int)Grade) + "%");
	return true;
}

PickByFill::~PickByFill()
{
}
