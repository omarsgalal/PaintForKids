#include "CLine.h"
#include "fstream"

CLine::CLine(Point P1, Point P2, GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo, id)
{
	Start = P1;
	End = P2;
}

CLine::CLine()
{ }

void CLine::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->Drawline(Start, End, FigGfxInfo, Selected);
}

Point CLine::GetCenter() const
{
	return{ (Start.x + End.x) / 2.0,(Start.y + End.y) / 2.0 };
}


bool CLine::Rotate(Output* pOut, int degrees)
{
	Point center;
	center.x = (Start.x + End.x) / 2.0;
	center.y = (Start.y + End.y) / 2.0;
	rotatePoint(center, Start, degrees);
	rotatePoint(center, End, degrees);
	return CheckInBoundries(pOut, Start, End);
}


bool CLine::Move(Output* pOut, double X_diff, double Y_diff)
{
	Start.x += X_diff;
	Start.y += Y_diff;
	End.x += X_diff;
	End.y += Y_diff;

	if (CheckInBoundries(pOut, Start, End))
		return true;
	else
	{
		Start.x -= X_diff;
		Start.y -= Y_diff;
		End.x -= X_diff;
		End.y -= Y_diff;
		return false;
	}
}

bool CLine::Resize(Output* pOut, float Ratio)
{
	Point Center = GetCenter();
	Point NewStart = Start, NewEnd = End;
	resizeLine(Center, NewStart, Ratio);
	resizeLine(Center, NewEnd, Ratio);
	if (CheckInBoundries(pOut, NewStart, NewEnd))
	{
		Start = NewStart;
		End = NewEnd;
		return true;
	}
	else
		return false;
}

void CLine::RandomCoordinates(Output* pOut)
{
	Point*Left, *Right, *Up, *Down;
	if (Start.x > End.x)
	{
		Right = &Start;
		Left = &End;
	}
	else
	{
		Right = &End;
		Left = &Start;
	}

	double X_diff = Right->x - Left->x;

	do
	{
		srand((time(NULL)) ^ 2);
		Right->x = rand() % ((int)(0.5*pOut->GetWidth() - X_diff) + 1) + (0.5*pOut->GetWidth() + X_diff);
		Left->x = Right->x - X_diff;
	} while (!CheckInBoundries(pOut, Start, End, POINTINBOUNDARIES, 0));

	if (Start.y < End.y)
	{
		Up = &Start;
		Down = &End;
	}
	else
	{
		Up = &End;
		Down = &Start;
	}

	double Y_diff = Down->y - Up->y;

	do
	{
		srand((time(NULL)) ^ 2);
		Down->y = rand() % ((pOut->GetHeight() - pOut->GetStatusBarHeight()) - (pOut->GetToolBarHeight() + (int)Y_diff) + 1) + (pOut->GetToolBarHeight() + (int)Y_diff);
		Up->y = Down->y - Y_diff;
	} while (!CheckInBoundries(pOut, Start, End, POINTINBOUNDARIES, 0));
}

void CLine::ResizeHalfLeft()
{
	Start.x = Start.x / 2.0;
	End.x = End.x / 2.0;
	Start.x = (Start.x);
	Start.y = (Start.y);
	End.x = (End.x);
	End.y = (End.y);
}

void CLine::PrintInfo(Output* pOut)
{
	string Output = "";
	Output += "|| LINE ||  ID: ";
	Output += to_string(ID);
	Output += " Corner1 (";
	Output += to_string((int)Start.x);
	Output += ",";
	Output += to_string((int)Start.y);
	Output += "), Corner2 (";
	Output += to_string((int)End.x);
	Output += ",";
	Output += to_string((int)End.y);
	Output += ") Borderwidth : ";
	Output += to_string(FigGfxInfo.BorderWdth);
	Output += " Lenght :";
	Output += to_string((int)GetArea());

	pOut->PrintMessage(Output);
}

void CLine::Save(ofstream &OutFile, Output* pOut)
{
	OutFile << "LINE\t";
	OutFile << ID << "\t";
	OutFile << Start.x << "\t" << Start.y << "\t";
	OutFile << End.x << "\t" << End.y << "\t";
	OutFile << FigGfxInfo.BorderWdth << "\t";
	OutFile << pOut->GetColorIndex(FigGfxInfo.DrawClr) << "\n";
}

void CLine::Load(ifstream &InFile, Output* pOut)
{
	int color;
	InFile >> ID >> Start.x >> Start.y >> End.x >> End.y >> FigGfxInfo.BorderWdth >> color;
	FigGfxInfo.DrawClr = pOut->GetColorByIndex(color);

	FigGfxInfo.isFilled = false;

	if (ID > FigureCount)
		FigureCount = ID;
}

double CLine::LengthOfLine(Point P1, Point P2) {
	return sqrt((pow((P2.x - P1.x), 2)) + (pow((P2.y - P1.y), 2)));
}

bool CLine::CheckCoordinates(double X, double Y) {
	Point P;
	P.x = X;
	P.y = Y;

	double smaller_x, greater_x, smaller_y, greater_y;
	if (Start.x < End.x)
	{
		smaller_x = Start.x;
		greater_x = End.x;
	}
	else
	{
		smaller_x = End.x;
		greater_x = Start.x;
	}

	if (Start.y < End.y)
	{
		smaller_y = Start.y;
		greater_y = End.y;
	}
	else
	{
		smaller_y = End.y;
		greater_y = Start.y;
	}



	double distance = fabs((End.x - Start.x)*(Start.y - P.y) - (Start.x - P.x)*(End.y - Start.y)) / sqrt(pow(End.x - Start.x, 2) + pow(End.y - Start.y, 2));

	if (distance >= 0 && distance <= FigGfxInfo.BorderWdth / 2.0 && P.x < greater_x && P.x > smaller_x && P.y < greater_y && P.y > smaller_y)
	{
		return true;
	}
	return false;
}


CFigure* CLine::Copy(bool i)
{
	if (i == true)
		return new CLine(Start, End, FigGfxInfo, ID);
	else
		return new CLine(Start, End, FigGfxInfo);
}

double CLine::GetArea()
{
	return sqrt(pow((Start.x - End.x), 2) + pow((Start.y - End.y), 2)) * FigGfxInfo.BorderWdth;
}

TYPE CLine::GetType()
{
	return TLINE;
}
