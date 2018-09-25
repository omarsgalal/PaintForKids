#include "ChangeBorderWidth.h"

#include "..\..\ApplicationManager.h"



ChangeBorderWidth::ChangeBorderWidth(ApplicationManager *pApp) :Action(pApp)
{
	BorderWidth = -1;
	if (numSelectedFigs > 0)
	{
		PreviousBorderWidth = new int[numSelectedFigs];
		for (int i = 0; i < numSelectedFigs; i++) {
			PreviousBorderWidth[i] = pManager->GetfigBorderwidthByID(IDlist[i]);
		}
	}
	else
		previousBorderWidth = pManager->GetOutput()->getCrntPenWidth();
}

void ChangeBorderWidth::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->CreateBorderBar();
	pOut->PrintMessage("Choose the size of DrawPen ");
	ActType = pIn->GetUserAction(CHANGEBORDERWEIDTHBAR);
	switch (ActType)
	{
	case BORDERBY1:
		BorderWidth = 1;
		break;
	case BORDERBY3:
		BorderWidth = 3;
		break;
	case BORDERBY8:
		BorderWidth = 8;
		break;
	case BORDERBY12:
		BorderWidth = 12;
		break;
	default:
		break;
	}
}

bool ChangeBorderWidth::Execute(ActionType *&ActionSelected)
{
	ReadActionParameters();
	Output* pOut = pManager->GetOutput();
	if (BorderWidth == -1)
	{
		ActionSelected = &ActType;
		pManager->UpdateInterface();
		pManager->GetOutput()->ClearStatusBar();
		return false;
	}
	if (!pManager->ChangeAllBorderWidth(BorderWidth))
	{
		pOut->SetCrntPenWidth(BorderWidth);
		pManager->GetOutput()->PrintMessage("Change PenWidth to " + to_string(BorderWidth));
	}
	else
	{
		pManager->GetOutput()->PrintMessage("Change BorderWidth to " + to_string(BorderWidth) + " for " + to_string(numSelectedFigs) + " Figures ");
	}
	return true;
}

void ChangeBorderWidth::Undo()
{
	Action::Undo();
	Output*pOut = pManager->GetOutput();

	if (numSelectedFigs == 0)
	{
		pOut->SetCrntPenWidth(previousBorderWidth);
		pManager->GetOutput()->PrintMessage("Undo Changing PenWidth from " + to_string(previousBorderWidth) + " to " + to_string(BorderWidth));
	}
	else
	{
		for (int i = 0; i < numSelectedFigs; i++)
			pManager->ChangeBorderwidthByID(PreviousBorderWidth[i], IDlist[i]);
		pManager->GetOutput()->PrintMessage("Undo Changing BorderWidth to " + to_string(BorderWidth) + " for " + to_string(numSelectedFigs) + " Figures ");
	}
}

void  ChangeBorderWidth::Redo()
{
	Action::Redo(); //Redo
	Output*pOut = pManager->GetOutput();
	if (!pManager->ChangeAllBorderWidth(BorderWidth))
	{
		pOut->SetCrntPenWidth(BorderWidth);
		pManager->GetOutput()->PrintMessage("Redo Changing PenWidth to " + to_string(BorderWidth));
	}
	else
		pManager->GetOutput()->PrintMessage("Redo Changing BorderWidth to " + to_string(BorderWidth)+ " for "+ to_string(numSelectedFigs)+" Figures ");

}

ChangeBorderWidth::~ChangeBorderWidth()
{ }
