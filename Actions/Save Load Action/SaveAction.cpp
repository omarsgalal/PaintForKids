#include "SaveAction.h"
#include "..\..\ApplicationManager.h"

SaveAction::SaveAction(ApplicationManager * pApp) :Action(pApp)
{ }

void SaveAction::ReadActionParameters()
{
	Output*pOut=pManager->GetOutput();
	Input*pIn = pManager->GetInput();
	pOut->PrintMessage(" Enter File Name to save to : ");
	FileName = pIn->GetSrting(pOut);
	FileName += ".txt";
}

bool SaveAction::Execute(ActionType *&ActionSelected)
{
	ReadActionParameters();
	ofstream OutFile;
	OutFile.open(FileName, ios::out);
	pManager->SaveAll(OutFile);
	OutFile.close();
	pManager->GetOutput()->PrintMessage("Graph saved successfully to " + FileName);
	return true;
}

void SaveAction::Undo()
{ }

void  SaveAction::Redo()
{ }

SaveAction::~SaveAction()
{ }
