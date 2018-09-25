#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include "DEFS.h"
#include "Figures\CFigure.h"
#include "GUI\input.h"
#include "GUI\output.h"
#include "Actions\Action.h"
#include <list>

//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 , /*Max no of figures*/ MaxSavedAction = 100  /*MaxSaved Action in UndoList*/ };	

private:

	int FigCount;		//Actual number of figures
	int SelectedFigures; //Actual Number of Selected Figures
	bool Saved;
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	CFigure** CopiedList;
	int CopiedListSize;
	list<Action*> UndoList ;
	list<Action*> RedoList;
	list<CFigure*> Clipboard;

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

	//utility functions
	void AddToUndoList(Action* pAct); //add actions to undo list

	void ClearClipboard(); //clears the Clipboard

	CFigure* GetFigByID(int id);	//reutrns a pointer to the figure by its id

	void DestroyFigList();		//Destroy FigList before Load


public:	
	ApplicationManager(); 
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	ActionType GetUserAction(BarType = NOBAR) const;
	void ExecuteAction(ActionType&) ; //Creates an action and executes it

    // -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output

	void UpdateInterface() const;	//Redraws all the drawing window
	void UpdateInterface(CFigure**&, CFigure**&, int) const; //Overloaded for Scramble And Find Game
	
	// -- Figures Management Functions
	void AddFigure(CFigure* pFig); //Adds a new figure to the FigList
	CFigure *GetFigure(double x, double y) const; //Search for a figure given a point inside the figure


	 ///////////////////////////// -- Action Execution Fucntions --  /////////////////////////////

	////////////////////////////////////////////////
	// -- Move / Rotate / Resize / Zoom Actions
	bool ResizeAll(float Ratio);		//Loop on all Figures to Resize all selected figures
	bool MoveAll(Point, double&, double&);	//Loop on all Figures to move all selected
	bool MoveFigs(double, double);
	bool RotateAll(int degrees); //loop in all figures and call the rotate function on them
	void AxesTransition(Point&P);

	////////////////////////////////////////////////
	// -- SendBack / BringFront Actions
	void SendBackAll();		//Loop on all Figures to send all selected figures back
	void BringFrontAll();	//Loop on all Figures to bring all selected figures front

	////////////////////////////////////////////////
	// -- Copy / Cut / Paste / Delete Actions
	void CopyAll(); //loop and call copy function of each figure
	bool CutAll(CFigure**&CutList);	//Loop on all Figures to cut all selected
	bool CheckClipboard();	//Check wheather Clipboard is empty or not
	bool PasteAll(Point, double&, double&, CFigure**); //paste figures in the Clipboard
	bool DeleteAll(CFigure** &DeletedList);//Loop on all Figures to delete all selected
	bool DeleteLastFig();	//deletes last figure in the figlist
	int GetClipboardSize();

	////////////////////////////////////////////////
	// -- Change Color/BorderWeidth Action
	bool ChangeAllFillColor(color fillColor); //loop on all figures to change fill color
	bool ChangeAllBorderColor(color borderColor); //loop on all figures to change boerder color
	bool ChangeAllBorderWidth(int borderWidth); //loop on all figures to change boerder width
	void SetFigFilledByID(int, bool); //Set Figure Filled or not by its id
	int GetfigBorderwidthByID(int ID); //Get BorderWidth of Figure by its id
	void ChangeBorderwidthByID(int Borderwidth, int iD); //change BorderWidth of Figure by its id
	color GetFigFillColorByID(int id);	//returns the color of the specified figure
	color GetFigBorderColorByID(int id); //returns the color of the specified figure
	void ChngFigBorderColorByID(color c, int id); //Set Border color of Figure by its id
	void ChngFigFillColorByID(color c, int id);   //Set Fill color of Figure by its id

	////////////////////////////////////////////////
	// -- Select Action
	void Select(double, double);
	void SelectFigsByID(int* IDlist, int size);	//selects figures by ids 
	void UnselectAll();		 //unselect all figures
	bool GraphisSaved()const; //returns true if the Graph is saved

	////////////////////////////////////////////////
	// -- Save / Load Actions
	void SaveAll(ofstream&OutFile); //Loop on all Figures to save each in file
	void LoadAll(ifstream&InputFile); //Loop on all Figures to load each from file

	////////////////////////////////////////////////
	// -- Functions to execute Undo Action

	int* GetIDList(int&) const;	//returns array of selected figures' IDs
	int* GetIndexList()const;	//return array of index of selected element in FigList
	int GetFigIdByPoint(double x, double y); //return id of fig by point on it
	void DeleteFigByID(int id);	//delete Figure from FigList by its id
	int GetFigCount();	//return Figure Count
	int* GetIDAllList();//return array of ids of all figures
	bool FigIsFilled(int id);//return true if the figure of id is Filled of not
	bool FigIsSelected(int id);//return true if the figure of id is Selected of not
	void AddFigbyIndex(int, int);//Get id of Figure and its index in list to return it to its real index

	Action* UndoLastAction();	// Get Last Action in UndoList and call function undo inside it
	Action* RedoLastAction();	// Get Last Action in RedoList and call function redo inside it

	////////////////////////////////////////////////
	// -- Play mode Execution Fucntions

	void ExchangeList(bool Exchange); //Exchange : 0 at begging of game and 1 in the end of the game to change back the two lists
	void CreateScrambleAndFindList(CFigure**&, CFigure**&, int&); //Create Scramble and find List and Get Random Coordinates
	TYPE GetFigureType(double x, double y);	//Get Type of Figure by a point on it
	double GetFigAreaById(int id);	//Get Figure area by its id
	int GetTypeCount(TYPE t);	//Get number of Figures of Type t
	int GetFillColorCount(color C, bool Filled);	//Get number of Figures of color C
	int GetTypeFillCount(TYPE t, color C, bool Filled);	//Get number of Figures of type t and color C

	~ApplicationManager();
};

#endif