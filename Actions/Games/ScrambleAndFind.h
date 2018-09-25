#pragma once
#include "..\Action.h"
#include "..\..\Figures\CFigure.h"

class ScrambleAndFind : public Action
{
private:
	CFigure**OriginalFigList;
	CFigure**ScrambleAndFindFigList;
	int Size;
	int index;
	bool exit;
	int ValidPicks;
	int InvalidPicks;
public:
	ScrambleAndFind(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	void DeletePickedFigure();

	CFigure * GtFigure(Point);

	//To undo this action 
	virtual void Undo();

	//To redo this action
	virtual void Redo();

	virtual bool Execute(ActionType *&);

	virtual ~ScrambleAndFind();
};

