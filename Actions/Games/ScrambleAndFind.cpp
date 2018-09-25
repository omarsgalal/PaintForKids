#include "ScrambleAndFind.h"
#include "..\..\ApplicationManager.h"


ScrambleAndFind::ScrambleAndFind(ApplicationManager *pApp) :Action (pApp)
{
	exit = false;
	ValidPicks = 0;
	InvalidPicks = 0;
	OriginalFigList = NULL;
	ScrambleAndFindFigList = NULL;
}

void ScrambleAndFind::DeletePickedFigure()
{
	delete ScrambleAndFindFigList[index];
	delete OriginalFigList[index];
	for (int i = index; i < Size-1 ; i++)
	{
		OriginalFigList[i] = OriginalFigList[i + 1];
		OriginalFigList[i + 1] = NULL;
		ScrambleAndFindFigList[i] = ScrambleAndFindFigList[i + 1];
		ScrambleAndFindFigList[i+1] = NULL;
	}
	Size--;
}
CFigure* ScrambleAndFind::GtFigure(Point P)
{
	for (int i = Size - 1 ; i >=0 ; i--)
		if (ScrambleAndFindFigList[i]->CheckCoordinates(P.x, P.y))
			return ScrambleAndFindFigList[i];
	return NULL;

}
void ScrambleAndFind::ReadActionParameters()
{
	Point P; 
	Output*pOut = pManager->GetOutput();
	Input*pIn = pManager->GetInput();
	bool FigNotFound = true;
	 while (FigNotFound)
	 {
		 ActType = pManager->GetUserAction();
		 if (ActType != DRAWING_AREA && ActType != STATUS && ActType != EMPTY)
			 break;
		 P = pIn->GetLastPoint();
		 CFigure*fig = GtFigure(P);
		 if (ScrambleAndFindFigList[index]== fig )
		 {
			 DeletePickedFigure();
			 pManager->UpdateInterface(OriginalFigList, ScrambleAndFindFigList, Size);
			 ValidPicks++;
			 FigNotFound = false;
		 }
		 else if (fig != NULL )
			 InvalidPicks++;

		 pOut->PrintMessage("Valid Picks = "+to_string(ValidPicks)+"\t Invalid Picks = "+to_string(InvalidPicks));
		 
	 }
}

bool ScrambleAndFind::Execute(ActionType *&ActionSelected)
{

	if (pManager->GetFigCount() == 0)
	{
		pManager->GetOutput()->PrintMessage("There are no figures to play !");
		return false;
	}

	Output*pOut = pManager->GetOutput();
	Input*pIn = pManager->GetInput();

	pManager->CreateScrambleAndFindList(OriginalFigList,ScrambleAndFindFigList,Size);

	pManager->UpdateInterface(OriginalFigList, ScrambleAndFindFigList, Size);

	pOut->PrintMessage("Scramble And Find Game is Selected .. Click anywhere to begin the Game");

	ActType = pManager->GetUserAction();

	pOut->ClearStatusBar();

	srand(time(NULL));

	while (ActType == DRAWING_AREA && Size!=0 )
	{
		index = rand() % (Size);
		OriginalFigList[index]->SetSelected(1);
		pManager->UpdateInterface(OriginalFigList, ScrambleAndFindFigList, Size);
		ReadActionParameters(); 
	}
	if (ActType == DRAWING_AREA || ActType == STATUS || ActType == EMPTY)
	{
		int Perecnt =  ((float)ValidPicks / (ValidPicks+InvalidPicks))*100;
		pOut->PrintMessage("The Game ended .. You got " + to_string(Perecnt) + " % ");
		return true;
	}
	else
	{
		pOut->ClearStatusBar();
		ActionSelected = &ActType;
		return false;
	}
	

}

void ScrambleAndFind::Undo()
{ }

void  ScrambleAndFind::Redo()
{ }

ScrambleAndFind::~ScrambleAndFind()
{
	if (Size != 0)
		for (int i = 0; i < Size; i++)
		{
			delete OriginalFigList[i];
			delete ScrambleAndFindFigList[i];
		}
	delete[]OriginalFigList;
	delete[]ScrambleAndFindFigList;
}
