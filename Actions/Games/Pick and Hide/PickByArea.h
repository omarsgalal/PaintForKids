#pragma once
#include "..\..\Action.h"
#include "..\..\..\Figures\CFigure.h"

struct Node
{
	double Area;
	int*pId;
};

class PickByArea : public Action
{
	int valid, inValid;
	Point P;
	Node* AreaList;
	int figCount;
	int* IDAllList;
	int id;

	void PickAppropriateFig(int last);

public:
	PickByArea(ApplicationManager* pApp);

	virtual ~PickByArea();

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters();

	//Execute action (code depends on action type)
	virtual bool Execute(ActionType *&);

	void SortAreaList();

	void ReverseAreaList();

	//To undo this action (code depends on action type)
	virtual void Undo();

	//To redo this action (code depends on action type)
	virtual void Redo();
};

