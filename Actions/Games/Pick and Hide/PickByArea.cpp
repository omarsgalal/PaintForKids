#include "PickByArea.h"

#include "..\..\..\ApplicationManager.h"

PickByArea::PickByArea(ApplicationManager* pApp):Action(pApp)
{
	valid = inValid = 0;

	figCount = pManager->GetFigCount();
	IDAllList = pManager->GetIDAllList();
	AreaList = new Node[figCount];
	for (int i = 0; i < figCount; i++)
	{
		AreaList[i].Area = pManager->GetFigAreaById(IDAllList[i]);
		AreaList[i].pId = &IDAllList[i];
	}
	SortAreaList();
}


PickByArea::~PickByArea()
{ }


void PickByArea::ReadActionParameters()
{
	ActType = pManager->GetUserAction();
	if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
		return;
	P = pManager->GetInput()->GetLastPoint();
	id = pManager->GetFigIdByPoint(P.x, P.y);
}


bool PickByArea::Execute(ActionType *&ActionSelected)
{

	pManager->GetOutput()->PrintMessage("Select the largest or the smallest figure");
	do
	{
		ReadActionParameters();
		if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
		{
			pManager->GetOutput()->ClearStatusBar();
			ActionSelected = &ActType;
			return false;
		}
	} while (id == -1 || (pManager->GetFigAreaById(id) != AreaList[0].Area && pManager->GetFigAreaById(id) != AreaList[figCount - 1].Area));
	double FigArea = pManager->GetFigAreaById(id);
	if (FigArea == AreaList[0].Area)
	{
		ReverseAreaList();
		pManager->GetOutput()->PrintMessage("You Selected from Smallest to Largest");
	}
	else
		pManager->GetOutput()->PrintMessage("You Selected from Largest to Smallest");

	PickAppropriateFig(figCount - 1);
	valid++;
	pManager->UpdateInterface();

	for (int i = 0; i < figCount-1; i++)
	{
		inValid--;
		do
		{
			if (id != -1) inValid++;
			pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(valid) + "\t Invalid Picks = " + to_string(inValid));
			ReadActionParameters();
			if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			{
				pManager->GetOutput()->ClearStatusBar();
				ActionSelected = &ActType;
				return false;
			}
		} while (id == -1 || (pManager->GetFigAreaById(id) != AreaList[figCount - i - 2].Area));
		valid++;
		PickAppropriateFig(figCount - i - 2);
		pManager->UpdateInterface();
		pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(valid) + "\t Invalid Picks = " + to_string(inValid));

	}
	int grade = valid / float(inValid + valid) * 100;
	
	pManager->GetOutput()->PrintMessage("Valid Picks = " + to_string(valid) + "\t Invalid Picks = " + to_string(inValid) + "\t your grade = " + to_string(grade) + "%");

	return true;
}


void PickByArea::SortAreaList()
{
	for (int i = 0; i < figCount; i++)
	{
		for (int j = figCount - 1; j > i; j--)
		{
			if (AreaList[j].Area < AreaList[j - 1].Area)
			{
				Node temp = AreaList[j];
				AreaList[j] = AreaList[j - 1];
				AreaList[j - 1] = temp;
			}
		}
	}
}


void PickByArea::ReverseAreaList()
{
	Node* reversedList = new Node[figCount];
	int j = figCount - 1;
	for (int i = 0; i < figCount; i++)
	{
		reversedList[j] = AreaList[i];
		j--;
	}
	delete[] AreaList;
	AreaList = reversedList;
}


void PickByArea::PickAppropriateFig(int last)
{
	int i;
	if (*(AreaList[last].pId) != id)
	{
		for (i = last-1; i >= 0; i--)
		{
			if (*(AreaList[i].pId) == id)
				break;
		}
		Node temp = AreaList[i];
		AreaList[i] = AreaList[last];
		AreaList[last] = temp;
	}
	pManager->DeleteFigByID(*(AreaList[last].pId));
}


void PickByArea::Undo()
{}

void PickByArea::Redo()
{}