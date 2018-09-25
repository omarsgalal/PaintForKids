#include "ChangeFillColor.h"

#include "..\..\ApplicationManager.h"


ChangeFillColor::ChangeFillColor(ApplicationManager *pApp) :Action(pApp)
{
	if (numSelectedFigs > 0)
	{
		Figscolors = new color[numSelectedFigs];
		wasFilled = new bool[numSelectedFigs];
		for (int i = 0; i < numSelectedFigs; i++)
		{
			Figscolors[i] = pManager->GetFigFillColorByID(IDlist[i]);
			wasFilled[i] = pManager->FigIsFilled(IDlist[i]);
		}
	}
	else
	{
		defFilled = pManager->GetOutput()->isFilled();
	}
}

void ChangeFillColor::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Changing Fill Color : Choose the new Color ");
	pOut->CreateColorBar();
	fillcolor = pIn->getColor();
	pOut->ClearStatusBar();
}

bool ChangeFillColor::Execute(ActionType *&ActionSelected)
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();
	if (fillcolor == NULL)
		return false;

	if (!pManager->ChangeAllFillColor(*fillcolor))
	{
		pOut->SetFilled(true);
		lastFillColor = pOut->getCrntFillColor();
		pOut->SetCrntFillColor(*fillcolor);
	}

	return true;
}

void ChangeFillColor::Undo()
{
	Output* pOut = pManager->GetOutput();
	Action::Undo();
	if (numSelectedFigs == 0)
	{
		pOut->SetFilled(defFilled);
		pOut->SetCrntFillColor(lastFillColor);
		pManager->GetOutput()->PrintMessage("Undo Changing default Fill Color");
	}
	else
	{
		for (int i = 0; i < numSelectedFigs; i++)
		{
			pManager->SetFigFilledByID(IDlist[i], wasFilled[i]);
			if (wasFilled[i])
				pManager->ChngFigFillColorByID(Figscolors[i], IDlist[i]);
		}
		pManager->GetOutput()->PrintMessage("Undo Changing Fill Color for "+ to_string(numSelectedFigs)+" Figures");
	}
}

void  ChangeFillColor::Redo()
{
	Output* pOut = pManager->GetOutput();
	Action::Redo();
	if (!pManager->ChangeAllFillColor(*fillcolor))
	{
		pOut->SetCrntFillColor(true);
		pOut->SetCrntFillColor(*fillcolor);
		pManager->GetOutput()->PrintMessage("Redo Changing default Fill Color");
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Redo Changing Fill Color for " + to_string(numSelectedFigs) + " Figures");
	}
}


ChangeFillColor::~ChangeFillColor()
{
	if (numSelectedFigs != 0)
	{
		delete[] Figscolors;
		delete[] wasFilled;
	}
}