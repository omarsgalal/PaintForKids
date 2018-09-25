#include "CTriangle.h"
#include <fstream>

CTriangle::CTriangle(Point P1, Point P2,Point P3 , GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo, id)
{
	Corner1 = P1;
	Corner2 = P2;
	Corner3 = P3;
}

CTriangle::CTriangle()
{ }

void CTriangle::Draw(Output* pOut) const
{
	pOut->Drawtriangle(Corner1, Corner2,Corner3, FigGfxInfo, Selected);
}

Point CTriangle::GetCenter() const
{
	return{ (Corner1.x + Corner2.x + Corner3.x) / 3.0 ,  (Corner1.y + Corner2.y + Corner3.y) / 3.0 };
}


bool CTriangle::Rotate(Output* pOut, int degrees) 	//Rotate the figure
{
	Point Center = GetCenter();

	rotatePoint(Center, Corner1, degrees);
	rotatePoint(Center, Corner2, degrees);
	rotatePoint(Center, Corner3, degrees);
	return CheckInBoundries(pOut, Corner1, Corner2, Corner3);
}

bool CTriangle::Resize(Output* pOut, float Ratio)	//Resize the figure
{
	Point Center = GetCenter();

	Point NewCorner1 = Corner1, NewCorner2 = Corner2, NewCorner3 = Corner3;
	resizeLine(Center, NewCorner1, Ratio);
	resizeLine(Center, NewCorner2, Ratio);
	resizeLine(Center, NewCorner3, Ratio);
	if (CheckInBoundries(pOut, NewCorner1, NewCorner2, Corner3))
	{
		Corner1 = NewCorner1;
		Corner2 = NewCorner2;
		Corner3 = NewCorner3;
		return true;
	}
	else
		return false;
}

bool CTriangle::Move(Output* pOut, double X_diff, double Y_diff)		//Move the figure
{
	Corner1.x += X_diff;
	Corner1.y += Y_diff;
	Corner2.x += X_diff;
	Corner2.y += Y_diff;
	Corner3.x += X_diff;
	Corner3.y += Y_diff;

	if (CheckInBoundries(pOut, Corner1, Corner2, Corner3))
		return true;
	else
	{
		Corner1.x -= X_diff;
		Corner1.y -= Y_diff;
		Corner2.x -= X_diff;
		Corner2.y -= Y_diff;
		Corner3.x -= X_diff;
		Corner3.y -= Y_diff;
		return false;
	}
}


void CTriangle::RandomCoordinates(Output* pOut)
{
	srand(time(NULL) + ID);
	Point*Right, *FirstLeft, *SecondLeft, *Down, *FirstUp, *SecondUp;

	if (Corner1.x > Corner2.x && Corner1.x > Corner3.x)
	{
		Right = &Corner1;
		FirstLeft = &Corner2;
		SecondLeft = &Corner3;
	}
	else if (Corner2.x > Corner1.x && Corner2.x > Corner3.x)
	{
		Right = &Corner2;
		FirstLeft = &Corner1;
		SecondLeft = &Corner3;
	}
	else
	{
		Right = &Corner3;
		FirstLeft = &Corner1;
		SecondLeft = &Corner2;
	}

	double X_diff2 = Right->x - FirstLeft->x;
	double X_diff3 = Right->x - SecondLeft->x;
	double Max_X_diff = max(X_diff2, X_diff3);

	do
	{
		Right->x = rand() % ((int)(0.5*pOut->GetWidth()) - (int)Max_X_diff + 1) + (0.5*pOut->GetWidth() + Max_X_diff);
		FirstLeft->x = Right->x - X_diff2;
		SecondLeft->x = Right->x - X_diff3;
	} while (!CheckInBoundries(pOut, Corner1, Corner2, Corner3, 0));



	if (Corner1.y > Corner2.y && Corner1.y > Corner3.y)
	{
		Down = &Corner1;
		FirstUp = &Corner2;
		SecondUp = &Corner3;
	}
	else if (Corner2.y > Corner1.y && Corner2.y > Corner3.y)
	{
		Down = &Corner2;
		FirstUp = &Corner1;
		SecondUp = &Corner3;
	}
	else
	{
		Down = &Corner3;
		FirstUp = &Corner1;
		SecondUp = &Corner2;
	}

	double Y_diff2 = Down->y - FirstUp->y;
	double Y_diff3 = Down->y - SecondUp->y;
	double Max_Y_diff = max(Y_diff2, Y_diff3);

	do
	{
		Down->y = rand() % ((pOut->GetHeight() - pOut->GetStatusBarHeight()) - (pOut->GetToolBarHeight() + (int)Max_Y_diff) + 1) + (pOut->GetToolBarHeight() + (int)Max_Y_diff);
		FirstUp->y = Down->y - Y_diff2;
		SecondUp->y = Down->y - Y_diff3;
	} while (!CheckInBoundries(pOut, Corner1, Corner2, Corner3, 0));
}

void CTriangle::ResizeHalfLeft()
{
	Corner1.x = Corner1.x / 2.0;
	Corner2.x = Corner2.x / 2.0;
	Corner3.x = Corner3.x / 2.0;
}


void CTriangle::Save(ofstream &OutFile, Output* pOut)	//Save the figure parameters to the file
{
	OutFile << "TRIANG\t";
	OutFile << ID << "\t";
	OutFile << Corner1.x << "\t" << Corner1.y << "\t";
	OutFile << Corner2.x << "\t" << Corner2.y << "\t";
	OutFile << Corner3.x << "\t" << Corner3.y << "\t";
	OutFile << FigGfxInfo.BorderWdth << "\t";
	OutFile <<pOut->GetColorIndex(FigGfxInfo.DrawClr) << "\t";
	
	if (FigGfxInfo.isFilled)
		OutFile << pOut->GetColorIndex(FigGfxInfo.FillClr) <<"\n";
	else
		OutFile << "NO_FILL \n";
}

void CTriangle::Load(ifstream &InFile, Output* pOut)	//Load the figure parameters to the file
{
	int color; string fill;
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >> Corner3.x >> Corner3.y >> FigGfxInfo.BorderWdth >> color >> fill;

	FigGfxInfo.DrawClr = pOut->GetColorByIndex(color);

	if (fill == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr = pOut->GetColorByIndex(stoi(fill));
	}

	if (ID > FigureCount)
		FigureCount = ID;
}

void CTriangle::PrintInfo(Output* pOut)	//print all figure info on the status bar
{
	string Output = "";
	Output += "|| TRIANGLE ||  ID: ";
	Output += to_string(ID);
	Output += " Corner1 (";
	Output += to_string((int)Corner1.x);
	Output += ",";
	Output += to_string((int)Corner1.y);
	Output += "), Corner2 (";
	Output += to_string((int)Corner2.x);
	Output += ",";
	Output += to_string((int)Corner2.y);
	Output += "), Corner3 (";
	Output += to_string((int)Corner3.x);
	Output += ",";
	Output += to_string((int)Corner3.y);
	Output += ") Borderwidth : ";
	Output += to_string(FigGfxInfo.BorderWdth);
	Output += " Width :";
	Output += to_string ( sqrt( (Corner1.x - Corner2.x)*(Corner1.x - Corner2.x) + (Corner1.y - Corner2.y)*(Corner1.y - Corner2.y) ));
	Output += " Height :";
	Output += to_string((int)(GetArea() / sqrt((Corner1.x - Corner2.x)*(Corner1.x - Corner2.x) + (Corner1.y - Corner2.y)*(Corner1.y - Corner2.y)) ));
	Output += " Area :";
	Output += to_string((int)GetArea());
	Output += " Perimeter :";
	Output += to_string((int)( sqrt(pow((int)(Corner1.x - Corner2.x), 2) + pow((int)(Corner1.y - Corner2.y), 2)) + sqrt(pow((int)(Corner1.x - Corner3.x), 2) + pow((int)(Corner1.y - Corner3.y), 2)) + sqrt(pow((int)(Corner3.x - Corner2.x), 2) + pow((int)(Corner3.y - Corner2.y), 2)) ));

	pOut->PrintMessage(Output);
}


CFigure* CTriangle::Copy(bool i)
{
	if (i == true)
		return new CTriangle(Corner1, Corner2, Corner3, FigGfxInfo,ID);
	else
		return new CTriangle(Corner1, Corner2, Corner3, FigGfxInfo);
}

double CTriangle::sign(Point p1, Point p2, Point p3) //Function used in CheckCoordinates function
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool CTriangle::CheckCoordinates(double x, double y)
{
	bool b1, b2, b3;
	Point pt;
	pt.x = x; pt.y = y;
	b1 = sign(pt, Corner1, Corner2) < 0.0;
	b2 = sign(pt, Corner2, Corner3) < 0.0;
	b3 = sign(pt, Corner3, Corner1) < 0.0;

	return ((b1 == b2) && (b2 == b3));
}


TYPE CTriangle::GetType()
{
	return TTRIANGLE;
}


double CTriangle::GetArea()
{
	return fabs((Corner1.x*(Corner2.y - Corner3.y) + Corner2.x * (Corner3.y - Corner1.y) + Corner3.x * (Corner1.y - Corner2.y)) / 2.0);
}

CTriangle::~CTriangle()
{ }
