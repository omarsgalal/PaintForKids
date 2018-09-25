#include "ChangeBorderColor.h"
#include "..\..\ApplicationManager.h"


ChangeBorderColor::ChangeBorderColor(ApplicationManager *pApp) :Action(pApp)
{
	if (numSelectedFigs > 0)
	{
		FigsBorderColors = new color[numSelectedFigs];
		for (int i = 0; i < numSelectedFigs; i++)
		{
			FigsBorderColors[i] = pManager->GetFigBorderColorByID(IDlist[i]);
		}
	}
}

void ChangeBorderColor::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Changing Border Color : Choose the new Color ");
	pOut->CreateColorBar();
	BorderColor = pIn->getColor();
}

bool ChangeBorderColor::Execute(ActionType *&ActionSelected)
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();

	if (!pManager->ChangeAllBorderColor(*BorderColor))
	{
		LastBorderColor = pOut->getCrntDrawColor();
		pOut->SetCrntDrawColor(*BorderColor);
	}
	return true;
}


void ChangeBorderColor::Undo()
{
	Action::Undo();
	Output* pOut = pManager->GetOutput();
	if (numSelectedFigs == 0)
	{
		pOut->SetCrntDrawColor (LastBorderColor);
		pManager->GetOutput()->PrintMessage("Undo Changing default Border Color");

	}
	else
	{
		for (int i = 0; i < numSelectedFigs; i++)
		{
			pManager->ChngFigBorderColorByID(FigsBorderColors[i], IDlist[i]);
		}
		pManager->GetOutput()->PrintMessage("Undo Changing Border Color for " + to_string(numSelectedFigs) + " Figures");
	}
	pManager->GetOutput()->PrintMessage("Undo Changing Border Color");

}

void  ChangeBorderColor::Redo()
{
	Action::Redo();
	Output* pOut = pManager->GetOutput();
	if (!pManager->ChangeAllBorderColor(*BorderColor))
	{
		pOut->SetCrntDrawColor (*BorderColor);
	}

}

ChangeBorderColor::~ChangeBorderColor()
{ }


