#include "ApplicationManager.h"
#include "Actions\AllActionIncludes.h"
#include "Figures\AllFigureIncludes.h"
#include <fstream>

//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	FigCount = 0;
	SelectedFigures = 0;
	Saved = true;
	CopiedListSize = 0;
	CopiedList = NULL;
	//Create an array of figure pointers and set them to NULL		
	for (int i = 0; i < MaxFigCount; i++)
		FigList[i] = NULL;
}

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction(BarType BT) const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction(BT);
}

////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType&ActType)
{
	Action* pAct = NULL;
	ActionType *ActionSelected = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_LINE:
		pAct = new AddLineAction(this);
		break;
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case DRAW_TRI:
		pAct = new AddTriAction(this);
		break;
	case DRAW_CIRC:
		pAct = new AddCircleAction(this);
		break;
	case CHNG_CLR:
		pAct = new ChangeColorAction(this);
		break;
	case CHNG_BORDER_WIDTH:
		pAct = new ChangeBorderWidth(this);
		break;
	case ZOOM:
		pAct = new ZoomAction(this);
		break;
	case SELECT:
		pAct = new SelectAction(this);
		break;
	case MOVE:
		pAct = new MoveAction(this);
		break;
	case RESIZE:
		pAct = new ResizeAction(this);
		break;
	case ROTATE:
		pAct = new RotateAction(this);
		break;
	case SEND_BACK:
		pAct = new SendBackAction(this);
		break;
	case BRNG_FRNT:
		pAct = new BringFrontAction(this);
		break;
	case COPY:
		pAct = new CopyAction(this);
		break;
	case CUT:
		pAct = new CutAction(this);
		break;
	case PASTE:
		pAct = new PasteAction(this);
		break;
	case DEL:
		pAct = new DeleteAction(this);
		break;
	case UNDO:
		pAct = new UndoAction(this);
		break;
	case REDO:
		pAct = new RedoAction(this);
		break;
	case SAVE:
		pAct = new SaveAction(this);
		break;
	case LOAD:
		pAct = new LoadAction(this);
		break;
	case EXIT:
		pAct = new ExitAction(this);
		break;
	case PICKANDHIDE_GAME:
		pAct = new PickAndHide(this);
		break;
	case SCRAMBLEANDFIND_GAME:
		pAct = new ScrambleAndFind(this);
		break;
	case TO_DRAW:
		pOut->SetInterfaceMode(MODE_DRAW);
		pOut->ClearToolBar();
		pOut->CreateDrawToolBar();
		break;
	case TO_PLAY:
		pOut->SetInterfaceMode(MODE_PLAY);
		pOut->SetZoomFactor(1);
		pOut->ClearToolBar();
		pOut->CreatePlayToolBar();
		break;
	default:
		break;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		if (pAct->Execute(ActionSelected) && pOut->GetInterfaceMode() == DRAW_MODE )
		{
			if (ActType != SAVE && ActType != LOAD  && ActType != UNDO && ActType != REDO && ActType != EXIT && ActType != SELECT && ActType != ZOOM)
			{
				AddToUndoList(pAct);

				if (!RedoList.empty())
					RedoList.clear();
			}

			if (ActType != SAVE && ActType != LOAD && ActType != SELECT && ActType != EXIT && ActType != ZOOM )
				Saved = false;
			else
				Saved = true;

			if (ActType == EXIT)
				ActType = DRAWING_AREA;
		}
		else
		{
			if (ActionSelected != NULL)
				ExecuteAction(*ActionSelected);
			delete pAct; //Action is not needed any more ==> delete it
		}

		pAct = NULL;
	}

}

//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if (FigCount < MaxFigCount)
		FigList[FigCount++] = pFig;
	if (pFig->IsSelected())
		SelectedFigures++;
}

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(double x, double y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL

	for (int i = FigCount - 1; i >= 0; i--)
		if (FigList[i]->CheckCoordinates(x, y))
			return FigList[i];
	return NULL;
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{
	pOut->ClearDrawArea();
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
	if (pOut->GetInterfaceMode() == DRAW_MODE)
		pOut->CreateDrawToolBar(!UndoList.empty(),!RedoList.empty());
	pOut->UpdateStatusBar();
}

void ApplicationManager::UpdateInterface(CFigure**&OriginalFigList, CFigure**&ScrambleAndFindFigList, int Size)const
{
	pOut->ClearDrawArea();
	GfxInfo LineGfx;
	LineGfx.BorderWdth = 5;
	LineGfx.DrawClr = pOut->GetStatusBarColor();
	pOut->Drawline({ (float)(pOut->GetWidth() / 2.0), (float)pOut->GetToolBarHeight()}, { (float)(pOut->GetWidth() / 2.0),(float)(pOut->GetHeight() - pOut->GetStatusBarHeight()) }, LineGfx);
	for (int i = 0; i < Size; i++)
	{
		OriginalFigList[i]->Draw(pOut);
		ScrambleAndFindFigList[i]->Draw(pOut);
	}
}

//==================================================================================//
//								Utility Functions		         					//
//==================================================================================//

void ApplicationManager::AddToUndoList(Action* pAct)
{
	if (UndoList.size() == MaxSavedAction)
	{
		delete UndoList.back();
		UndoList.pop_back();
	}
	UndoList.push_front(pAct);
}

void ApplicationManager::ClearClipboard()
{

	list<CFigure*>::const_iterator iterator;
	for (iterator = Clipboard.begin(); iterator != Clipboard.end(); ++iterator)
		delete *iterator;

	Clipboard.clear();
}

CFigure* ApplicationManager::GetFigByID(int id)
{
	CFigure* fig = NULL;
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID() == id)
		{
			fig = FigList[i];
			break;
		}
	}
	return fig;
}

void ApplicationManager::DestroyFigList()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	FigCount = 0;
}

////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{
	return pIn;
}

//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{
	return pOut;
}
////////////////////////////////////////////////////////////////////////////////////


//==================================================================================//
//				Move / Rotate / Resize / Zoom Actions Functions	 					//
//==================================================================================//

bool ApplicationManager::ResizeAll(float Ratio)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			if (!FigList[i]->Resize(pOut, Ratio))
			{
				for (int j = i - 1; j >= 0; j--)
					if (FigList[j]->IsSelected())
						FigList[j]->Resize(pOut, 1 / Ratio);
				return false;
			}
	return true;
}

bool ApplicationManager::MoveAll(Point P, double&diff_x, double&diff_y)
{
	int count = 0;

	Point CenterofFigs = { 0,0 };

	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			CenterofFigs.x += FigList[i]->GetCenter().x;
			CenterofFigs.y += FigList[i]->GetCenter().y;
			count++;
		}

	CenterofFigs.x /= count;
	CenterofFigs.y /= count;

	diff_x = (P.x - CenterofFigs.x);
	diff_y = (P.y - CenterofFigs.y);

	if (!MoveFigs(diff_x, diff_y))	return false;

	BringFrontAll();
	return true;
}


bool ApplicationManager::MoveFigs(double diff_x, double diff_y)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			if (!FigList[i]->Move(pOut, diff_x, diff_y))
			{
				for (int j = i - 1; j >= 0; j--)
					if (FigList[j]->IsSelected())
						FigList[j]->Move(pOut , -diff_x, -diff_y);
				return false;
			}
		}
	return true;
}

bool ApplicationManager::RotateAll(int degrees)
{
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			if (!FigList[i]->Rotate(pOut, degrees))
			{
				for (int j = i; j >= 0; j--)
					if (FigList[j]->IsSelected())
						FigList[j]->Rotate(pOut, (degrees + 180) % 360);
				return false;
			}
	return true;
}

void ApplicationManager::AxesTransition(Point&P)
{
	P.x -= 0.5*pOut->GetWidth();
	P.y -= 0.5*pOut->GetHeight();
	P.x /= sqrt(pOut->GetZoomFactor());
	P.y /= sqrt(pOut->GetZoomFactor());
	P.x += 0.5*pOut->GetWidth();
	P.y += 0.5*pOut->GetHeight();
}

//==================================================================================//
//							SendBack / BringFront Functions							//
//==================================================================================//


void ApplicationManager::SendBackAll()		//Loop on all Figures to send all selected figures back
{
	int j = 0;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			CFigure* temp = FigList[i];
			for (int k = i; k > j; k--)
				FigList[k] = FigList[k - 1];
			FigList[j++] = temp;
		}
}

void ApplicationManager::BringFrontAll()	//Loop on all Figures to bring all selected figures front
{
	int j = FigCount - 1;
	for (int i = j; i >= 0; i--)
		if (FigList[i]->IsSelected())
		{
			CFigure* temp = FigList[i];
			for (int k = i; k < j; k++)
				FigList[k] = FigList[k + 1];
			FigList[j--] = temp;
		}
}

//==================================================================================//
//						Copy / Cut / Paste / Delete Actions							//
//==================================================================================//

void ApplicationManager::CopyAll()
{
	ClearClipboard();
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			Clipboard.push_back(FigList[i]->Copy(true));
}

bool ApplicationManager::CutAll(CFigure**&CutList)
{
	if (SelectedFigures == 0) return false;
	ClearClipboard();
	int j = 0;
	CutList = new CFigure*[SelectedFigures];
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			CutList[j++] = FigList[i]->Copy(true);
			Clipboard.push_back(FigList[i]);
			FigList[i] = NULL;
		}

	int i = 0;
	j = 0;
	while (i < FigCount && j != (FigCount - SelectedFigures))
	{
		if (FigList[i] != NULL)
		{
			FigList[j] = FigList[i];
			if (i != j) FigList[i] = NULL;
			j++;
		}
		i++;
	}

	FigCount -= SelectedFigures;
	SelectedFigures = 0;
	return true;
}

bool ApplicationManager::CheckClipboard()
{
	return (!Clipboard.empty());
}

bool ApplicationManager::PasteAll(Point P, double&diff_x, double&diff_y, CFigure** pastedFigures)
{
	int count = 0;
	UnselectAll();

	list<CFigure*>::const_iterator iterator;

	for (iterator = Clipboard.begin(); iterator != Clipboard.end(); ++iterator) {
		CFigure* AddedFigure = (*iterator)->Copy(false);
		AddedFigure->SetSelected(true);
		AddFigure(AddedFigure);
		count++;
	}

	if (!MoveAll(P, diff_x, diff_y))
	{
		for (int i = FigCount - 1; i > FigCount - count - 1; i--)
		{
			delete FigList[i];
			FigList[i] = NULL;
		}
		FigCount -= count;
		return false;
	}
	SelectedFigures = count;
	for (int i = 0; i < count; i++)
	{
		pastedFigures[i] = FigList[FigCount - count + i]->Copy(true);
	}
	return true;
}

bool ApplicationManager::DeleteAll(CFigure**&DeletedList)
{
	int j = 0;
	DeletedList = new CFigure*[SelectedFigures];
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
		{
			DeletedList[j++] = FigList[i];
			FigList[i] = NULL;
			if (j == SelectedFigures) break;
		}
	int i = 0;
	j = 0;
	while (i < FigCount && j != (FigCount - SelectedFigures))
	{
		if (FigList[i] != NULL)
		{
			FigList[j] = FigList[i];
			if (i != j) FigList[i] = NULL;
			j++;
		}
		i++;
	}
	FigCount -= SelectedFigures;
	SelectedFigures = 0;

	return true;
}


bool ApplicationManager::DeleteLastFig()
{
	if (FigCount == 0)
		return false;
	if (FigList[FigCount - 1]->IsSelected()) SelectedFigures--;
	delete FigList[FigCount - 1];
	FigList[FigCount - 1] = NULL;
	FigCount--;
	return true;
}


int ApplicationManager::GetClipboardSize()
{
	return Clipboard.size();
}

//==================================================================================//
//						Change Color/BorderWeidth Actions							//
//==================================================================================//

bool ApplicationManager::ChangeAllFillColor(color fillColor)
{
	if (SelectedFigures == 0) return false;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			FigList[i]->ChngFillClr(fillColor);

	return true;
}


bool ApplicationManager::ChangeAllBorderColor(color borderColor)
{
	if (SelectedFigures == 0) return false;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			FigList[i]->ChngDrawClr(borderColor);

	return true;
}

bool ApplicationManager::ChangeAllBorderWidth(int borderWidth)
{
	if (SelectedFigures == 0) return false;
	for (int i = 0; i < FigCount; i++)
		if (FigList[i]->IsSelected())
			FigList[i]->ChngBorderWidth(borderWidth);

	return true;
}

void ApplicationManager::SetFigFilledByID(int id, bool isFilled)
{
	GetFigByID(id)->setFilled(isFilled);
}

int ApplicationManager::GetfigBorderwidthByID(int ID)
{
	return GetFigByID(ID)->GetBorderwidth();
}

void ApplicationManager::ChangeBorderwidthByID(int Borderwidth, int iD)
{
	GetFigByID(iD)->ChngBorderWidth(Borderwidth);
}

color ApplicationManager::GetFigFillColorByID(int id)
{
	return GetFigByID(id)->GetFillColor();
}

color ApplicationManager::GetFigBorderColorByID(int id)
{
	return GetFigByID(id)->GetBorderColor();
}

void ApplicationManager::ChngFigBorderColorByID(color c, int id)
{
	GetFigByID(id)->ChngDrawClr(c);
}

void ApplicationManager::ChngFigFillColorByID(color c, int id)
{
	GetFigByID(id)->ChngFillClr(c);
}

//==================================================================================//
//								Select Action										//
//==================================================================================//


void ApplicationManager::Select(double X, double Y)
{
	CFigure * SelectedFigure = GetFigure(X, Y);
	if (SelectedFigure == NULL)
		pOut->PrintMessage("No Figure is Selected, Choose another Figure!");
	else if (SelectedFigure->IsSelected())
	{
		SelectedFigure->SetSelected(0);
		SelectedFigures--;
	}
	else {
		SelectedFigure->SetSelected(1);
		SelectedFigures++;
	}

	if (SelectedFigures == 1)
	{
		int i = 0;
		while (true)
		{
			if (FigList[i]->IsSelected())
			{
				FigList[i]->PrintInfo(pOut);
				break;
			}
			i++;
		}
	}
	else
		pOut->PrintMessage("Number of selected Figures " + to_string(SelectedFigures));
	return;
}

void ApplicationManager::SelectFigsByID(int* IDlist, int size)
{
	int m = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < FigCount; j++)
		{
			if (IDlist[i] == FigList[j]->GetID())
			{
				FigList[j]->SetSelected(1);
				m++;
				break;
			}
		}
	}
	SelectedFigures = m;
}

void ApplicationManager::UnselectAll()
{
	for (int i = 0; i < FigCount && FigList[i] != NULL; i++)
		FigList[i]->SetSelected(false);
	SelectedFigures = 0;
}

bool ApplicationManager::GraphisSaved() const
{
	return Saved;
}


//==================================================================================//
//								Save / Load Actions									//
//==================================================================================//

void ApplicationManager::SaveAll(ofstream&OutFile)
{
	OutFile << pOut->GetColorIndex(pOut->getCrntDrawColor()) << "\t";
	OutFile << pOut->GetColorIndex(pOut->getCrntFillColor()) << "\t";
	OutFile << pOut->GetColorIndex(pOut->getBkgroundColor()) << "\t";
	OutFile << pOut->isFilled() << endl;
	OutFile << FigCount << "\n\n";
	for (int i = 0; i < FigCount; i++)
		FigList[i]->Save(OutFile, pOut);
}

void ApplicationManager::LoadAll(ifstream &InputFile)
{
	DestroyFigList();
	UndoList.clear();
	RedoList.clear();
	CFigure::LoadFigureCount();
	int NumberofFigures;
	int BackGroundColor, DrawColor, FillColor;bool isFilled;
	InputFile >> DrawColor >> FillColor >> BackGroundColor >> isFilled;
	pOut->SetCrntBkgroundColor(pOut->GetColorByIndex(BackGroundColor));
	pOut->SetCrntDrawColor(pOut->GetColorByIndex(DrawColor));
	pOut->SetCrntFillColor(pOut->GetColorByIndex(FillColor));
	pOut->SetFilled(isFilled);
	InputFile >> NumberofFigures;
	CFigure*AddedFigure;
	for (int i = 0; i < NumberofFigures; i++)
	{
		string type;
		InputFile >> type;
		if (type == "RECT")
			AddedFigure = new CRectangle;
		else if (type == "LINE")
			AddedFigure = new CLine;
		else if (type == "TRIANG")
			AddedFigure = new CTriangle;
		else
			AddedFigure = new CCircle;
		AddedFigure->Load(InputFile, pOut);
		AddFigure(AddedFigure);
	}
}

//==================================================================================//
//						Functions to execute Undo Action							//
//==================================================================================//

int* ApplicationManager::GetIDList(int&numSelectedFigs) const
{
	int* IDlist = NULL;
	numSelectedFigs = SelectedFigures;
	if (SelectedFigures > 0)
	{
		IDlist = new int[SelectedFigures];
		int j = 0;
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->IsSelected())
			{
				IDlist[j] = FigList[i]->GetID();
				j++;
			}
		}
	}
	return IDlist;
}

int* ApplicationManager::GetIndexList()const
{
	int* indexInList = NULL;
	if (SelectedFigures > 0)
	{
		indexInList = new int[SelectedFigures];
		int j = 0;
		for (int i = 0; i < FigCount; i++)
		{
			if (FigList[i]->IsSelected())
			{
				indexInList[j] = i;
				j++;
			}
		}
	}
	return indexInList;
}

int ApplicationManager::GetFigIdByPoint(double x, double y)
{
	CFigure* fig = GetFigure(x, y);

	if (fig == NULL)
		return -1;

	return fig->GetID();
}

void ApplicationManager::DeleteFigByID(int id)
{
	for (int i = 0; i < FigCount; i++)
	{
		if (FigList[i]->GetID() == id)
		{
			for (int j = i; j < FigCount - 1; j++)
			{
				FigList[j] = FigList[j + 1];
			}
			FigList[FigCount - 1] = NULL;
			FigCount--;
			break;
		}
	}
}

int ApplicationManager::GetFigCount()
{
	return FigCount;
}

int* ApplicationManager::GetIDAllList()
{
	int* IDlist = NULL;

	IDlist = new int[FigCount];
	int j = 0;
	for (int i = 0; i < FigCount; i++)
	{

		IDlist[j] = FigList[i]->GetID();
		j++;

	}
	return IDlist;
}

bool ApplicationManager::FigIsFilled(int id)
{
	return GetFigByID(id)->isFilled();
}

bool ApplicationManager::FigIsSelected(int id)
{
	return GetFigByID(id)->IsSelected();
}

void ApplicationManager::AddFigbyIndex(int id, int index)
{

	CFigure*Fig = GetFigByID(id);
	int i = 0;
	for (i; i < FigCount; i++)
		if (FigList[i] == Fig)
			break;

	if (i < index)
	{
		for (i; i < FigCount - 1; i++)
		{
			CFigure*temp = FigList[i];
			FigList[i] = FigList[i + 1];
			FigList[i + 1] = temp;
		}

	}
	else
	{
		for (int j = i; j > index; j--)
		{
			CFigure*temp = FigList[j];
			FigList[j] = FigList[j - 1];
			FigList[j - 1] = temp;
		}
	}
}


Action* ApplicationManager::UndoLastAction()
{
	if (UndoList.empty()) return NULL;
	Action* lastAct = UndoList.front();
	UndoList.pop_front();
	RedoList.push_front(lastAct);
	return lastAct;
}

Action * ApplicationManager::RedoLastAction()
{
	if (RedoList.empty()) return NULL;
	Action* lastAct = RedoList.front();
	RedoList.pop_front();
	UndoList.push_front(lastAct);
	return lastAct;
}

//==================================================================================//
//						Play mode Execution Fucntions								//
//==================================================================================//

void ApplicationManager::ExchangeList(bool Exchange)
{
	if (Exchange == false)
	{
		CopiedList = new CFigure*[FigCount];
		for (int i = 0; i < FigCount; i++)
			CopiedList[i] = FigList[i];
		CopiedListSize = FigCount;
	}
	else
	{
		FigCount = CopiedListSize;
		for (int i = 0; i < FigCount; i++)
			FigList[i] = CopiedList[i];
		delete[]CopiedList;
	}
}

void ApplicationManager::CreateScrambleAndFindList(CFigure**&OriginalFigList, CFigure**&ScrambleAndFindFigList, int&Size)
{
	Size = FigCount;
	ScrambleAndFindFigList = new CFigure*[Size];
	OriginalFigList = new CFigure*[Size];
	for (int i = 0; i < Size; i++)
	{
		OriginalFigList[i] = FigList[i]->Copy(true);
		OriginalFigList[i]->ResizeHalfLeft();
		ScrambleAndFindFigList[i] = OriginalFigList[i]->Copy(true);
		ScrambleAndFindFigList[i]->RandomCoordinates(pOut);
	}
}

TYPE ApplicationManager::GetFigureType(double x, double y) {
	CFigure* Temp = ApplicationManager::GetFigure(x, y);
	if (Temp == NULL)
	{
		return TYPE(-1);
	}
	return Temp->GetType();
}

double ApplicationManager::GetFigAreaById(int id)
{
	return GetFigByID(id)->GetArea();
}


int ApplicationManager::GetTypeCount(TYPE t) {
	int i = 0, count = 0;
	while (FigList[i] != NULL)
	{
		if (FigList[i]->GetType() == t)
		{
			count++;
		}
		i++;
	}
	return count;
}

int ApplicationManager::GetFillColorCount(color C, bool Filled) {
	int i = 0, count = 0;
	if (Filled)
	{
		while (FigList[i] != NULL)
		{
			if (FigList[i]->GetFillColor() == C)
			{
				count++;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while(FigList[i] != NULL)
		{
			if (!FigList[i]->isFilled())
			{
				count++;
			}
			i++;
		}
	}
	
	return count;
}


int ApplicationManager::GetTypeFillCount(TYPE t, color C, bool Filled) {
	int i = 0, count = 0;
	if (Filled)
	{
		while (FigList[i] != NULL)
		{
			if (FigList[i]->GetFillColor() == C && (FigList[i]->GetType() == t))
			{
				count++;
			}
			i++;
		}
	}
	else
	{
		i = 0;
		while (FigList[i] != NULL)
		{
			if (!FigList[i]->isFilled() && (FigList[i]->GetType() == t))
			{
				count++;
			}
			i++;
		}
	}

	return count;
}

////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for (int i = 0; i < FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
}
