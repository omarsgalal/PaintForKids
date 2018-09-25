#include "PickByType.h"

#include "ApplicationManager.h"



PickByType::PickByType(ApplicationManager* pApp):Action(pApp)
{
	Valid = InValid = Count = 0;
	T = TemporaryT = TYPE(-1);
}

void PickByType::ReadActionParameters() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	double x, y;
	pIn->GetPointClicked(x, y);
	if (T!=TYPE(-1))
	{
		while (TemporaryT == TYPE(-1))
		{
			if (x > 0 && x < UI.width && y>0 && y < UI.height)
				TemporaryT = pManager->GetFigureType(x, y);
		}
		if (TemporaryT == T)
		{
			Count--;
		}
			
	}
	else {
			while (T == TYPE(-1))
			{
				if (x > 0 && x < UI.width && y>0 && y < UI.height)
					T = pManager->GetFigureType(x, y);
			}
			Count = pManager->GetTypeCount(T);
	}
	return;
}

bool PickByType::Execute() {
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	ReadActionParameters();
	while (Count!=0)
	{
		ReadActionParameters();
		if (TemporaryT==T)
		{
			Valid++;
		}
		else InValid++;
	}
	Grade = (Valid / (Valid + InValid)) * 100;
	pOut->PrintMessage("Your Final Grade = " + to_string((int)Grade) + "%");
	return true;
}

void PickByType::Undo(){}

void PickByType::Redo() {}

PickByType::~PickByType()
{
}
