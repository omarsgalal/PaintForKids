#include "CRectangle.h"

CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo, int id):CFigure(FigureGfxInfo, id)
{
	Corner1 = P1;
	Corner2 = P2;
}

CRectangle::CRectangle()
{ }

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen	
	pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
}

Point CRectangle::GetCenter() const
{
	return{ (Corner1.x + Corner2.x) / 2.0 , (Corner1.y + Corner2.y) / 2.0 };
}

bool CRectangle::Move(Output* pOut, double X_diff, double Y_diff)
{
	Corner1.x += X_diff;
	Corner1.y += Y_diff;
	Corner2.x += X_diff;
	Corner2.y += Y_diff;

	if (CheckInBoundries(pOut, Corner1, Corner2))
		return true;
	else
	{
		Corner1.x -= X_diff;
		Corner1.y -= Y_diff;
		Corner2.x -= X_diff;
		Corner2.y -= Y_diff;
		return false;
	}
}


bool CRectangle::Resize(Output* pOut, float Ratio)
{
	Point Center = GetCenter();
	Point NewCorner1 = Corner1, NewCorner2 = Corner2;
	resizeLine(Center, NewCorner1, Ratio);
	resizeLine(Center, NewCorner2, Ratio);
	if (CheckInBoundries(pOut, NewCorner1, NewCorner2))
	{
		Corner1 = NewCorner1;
		Corner2 = NewCorner2;
		return true;
	}
	else
		return false;
}


bool CRectangle::CheckCoordinates(double x, double y)
{
	Point Left = Corner1;
	Point Right = Corner2; 
	if (Corner1.x > Corner2.x) {Left.x = Corner2.x; Right.x = Corner1.x;}
	if (Corner1.y > Corner2.y) {Left.y = Corner2.y; Right.y = Corner1.y;}
	Point P;
	P.x = x; P.y = y;
	if ((P.x >= Left.x) && (P.x <= Right.x) && (P.y >= Left.y) && (P.y <=Right.y))
		return true;
	else
		return false;
}

bool CRectangle::Rotate(Output* pOut, int degrees)
{
	Point Center = GetCenter();
	rotatePoint(Center, Corner1, degrees);
	rotatePoint(Center, Corner2, degrees);
	return CheckInBoundries(pOut, Corner1, Corner2);
}

void CRectangle::RandomCoordinates(Output* pOut)
{
	Point*Left, *Right, *Up, *Down;
	if (Corner1.x > Corner2.x)
	{
		Right = &Corner1;
		Left = &Corner2;
	}
	else
	{
		Right = &Corner2;
		Left = &Corner1;
	}

	double X_diff = Right->x - Left->x;

	do
	{
		srand((time(NULL)) ^ 2);
		Right->x = rand() % ((int)(0.5*pOut->GetWidth() - X_diff) + 1) + (0.5*pOut->GetWidth() + X_diff);
		Left->x = Right->x - X_diff;
	} while (!CheckInBoundries(pOut, Corner1, Corner2, POINTINBOUNDARIES, 0));

	if (Corner1.y < Corner2.y)
	{
		Up = &Corner1;
		Down = &Corner2;
	}
	else
	{
		Up = &Corner2;
		Down = &Corner1;
	}

	double Y_diff = Down->y - Up->y;

	do
	{
		srand((time(NULL)) ^ 2);
		Down->y = rand() % ((pOut->GetHeight() - pOut->GetStatusBarHeight()) - (pOut->GetToolBarHeight() + (int)Y_diff) + 1) + (pOut->GetToolBarHeight() + (int)Y_diff);
		Up->y = Down->y - Y_diff;
	} while (!CheckInBoundries(pOut, Corner1, Corner2, POINTINBOUNDARIES, 0));

}

void CRectangle::ResizeHalfLeft()
{
	Corner1.x = Corner1.x / 2.0;
	Corner2.x = Corner2.x / 2.0;
}

void CRectangle::PrintInfo(Output* pOut)
{
	string Output = "";
	Output += "|| RECTANGLE ||  ID: ";
	Output += to_string(ID);
	Output += " Corner1 (";
	Output += to_string((int)Corner1.x);
	Output += ",";
	Output += to_string((int)Corner1.y);
	Output += "), Corner2 (";
	Output += to_string((int)Corner2.x);
	Output += ",";
	Output += to_string((int)Corner2.y);
	Output += ") Borderwidth : ";
	Output += to_string(FigGfxInfo.BorderWdth);
	Output += " Width :";
	Output += to_string((int)(abs(Corner1.x - Corner2.x)));
	Output += " Height :";
	Output += to_string((int)abs(Corner1.y - Corner2.y));
	Output += " Area :";
	Output += to_string((int)GetArea());
	Output += " Perimeter :";
	Output += to_string((int)(2 * (abs(Corner1.x - Corner2.x) + abs(Corner1.y - Corner2.y))));

	pOut->PrintMessage(Output);
}


void CRectangle::Save(ofstream &OutFile, Output* pOut)
{
	OutFile << "RECT\t";
	OutFile << ID << "\t";
	OutFile << Corner1.x << "\t" << Corner1.y << "\t";
	OutFile << Corner2.x << "\t" << Corner2.y << "\t";
	OutFile << FigGfxInfo.BorderWdth << "\t";
	OutFile << pOut->GetColorIndex(FigGfxInfo.DrawClr) << "\t";

	if (FigGfxInfo.isFilled)
		OutFile << pOut->GetColorIndex(FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL \n";
}

void CRectangle::Load(ifstream&InFile, Output* pOut)
{
	int color; string fill;
	InFile >> ID >> Corner1.x >> Corner1.y >> Corner2.x >> Corner2.y >>FigGfxInfo.BorderWdth >> color >> fill;

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


CFigure* CRectangle::Copy(bool i)
{
	if (i == true)
		return new CRectangle(Corner1, Corner2, FigGfxInfo,ID);
	else
		return new CRectangle(Corner1, Corner2, FigGfxInfo);
}


double CRectangle::GetArea()
{
	return fabs((Corner1.x - Corner2.x)*(Corner1.y - Corner2.y));
}


TYPE CRectangle::GetType()
{
	return TRECTANGLE;
}