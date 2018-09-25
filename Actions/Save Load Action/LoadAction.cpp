#include "LoadAction.h"
#include"..\..\ApplicationManager.h"
#include "SaveAction.h"

LoadAction::LoadAction(ApplicationManager * pApp) :Action(pApp)
{ }

void LoadAction::ReadActionParameters()
{
	Output*pOut = pManager->GetOutput();
	Input*pIn = pManager->GetInput();
	pOut->PrintMessage(" Enter File Name to Load from : ");
	FileName = pIn->GetSrting(pOut);
	FileName += ".txt";
}

bool LoadAction::Execute(ActionType *&ActionSelected)
{
	Action*pAct;
	if (pManager->GetFigCount() != 0 && !pManager->GraphisSaved() )
	{
		ActType = pManager->GetOutput()->CreateExitWindow()->GetExitAction();
		if (ActType == SAVE)
		{
			pAct = new SaveAction(pManager);
			pAct->Execute(ActionSelected);
			delete pAct;
		}
		else if (ActType == DRAWING_AREA)
			return false;
	}

	ReadActionParameters();

	ifstream InputFile;

	InputFile.open(FileName, ios::in);

	if (InputFile)
	{
		pManager->LoadAll(InputFile);
		InputFile.close();
		pManager->GetOutput()->PrintMessage("Graph Loaded successfully from " + FileName);
		return true;
	}
	else
	{
		pManager->GetOutput()->PrintMessage(" No File with Name " + FileName + " to load from");
		return false;
	}

}

void LoadAction::Undo()
{ }

void  LoadAction::Redo()
{ }

LoadAction::~LoadAction()
{ }