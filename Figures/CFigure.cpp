#include "CFigure.h"

int CFigure::FigureCount = 0;

CFigure::CFigure(GfxInfo FigureGfxInfo, int id)
{ 
	if (id != 0)
		ID = id;
	else
		ID = ++FigureCount;
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
}

CFigure::CFigure()
{
	Selected = false;
}

void CFigure::LoadFigureCount()
{
	FigureCount = 0;
}

void CFigure::SetSelected(bool s)
{	Selected = s; }

bool CFigure::IsSelected() const
{	return Selected; }

int CFigure::GetBorderwidth() const
{
	return FigGfxInfo.BorderWdth;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::ChngBorderWidth(int borderWidth)
{
	FigGfxInfo.BorderWdth = borderWidth;
}

void CFigure::rotatePoint(Point Center, Point &rotatedPoint, int degrees)
{
	rotatedPoint.x -= Center.x;
	rotatedPoint.y -= Center.y;
	if (degrees == 270)
	{
		double auxPoint = rotatedPoint.x;
		rotatedPoint.x = -rotatedPoint.y;
		rotatedPoint.y = auxPoint;
	}
	else if (degrees == 90)
	{
		double auxPoint = rotatedPoint.x;
		rotatedPoint.x = rotatedPoint.y;
		rotatedPoint.y = -auxPoint;
	}
	else
	{
		rotatedPoint.x = -rotatedPoint.x;
		rotatedPoint.y = -rotatedPoint.y;
	}
	rotatedPoint.x += Center.x;
	rotatedPoint.y += Center.y;
}
void CFigure::resizeLine(Point Center, Point&resizedPoint, double Ratio)
{
	double k1, k2;

	k1 = abs(Ratio - 1); k2 = Ratio;

	if (Ratio > 1) k2 = -k2;

	resizedPoint.x = (k2*resizedPoint.x + k1*Center.x) / (k1 + k2);
	resizedPoint.y = (k2*resizedPoint.y + k1*Center.y) / (k1 + k2);

}

bool CFigure::CheckInBoundries(Output* pOut, Point P1, Point P2, Point P3, int Indicator) const
{
	if (Indicator == 1)
		return(pOut->GetToolBarHeight() < P1.y && P1.y < pOut->GetHeight() - pOut->GetStatusBarHeight() && pOut->GetToolBarHeight() < P2.y && P2.y < pOut->GetHeight() - pOut->GetStatusBarHeight() && pOut->GetToolBarHeight() < P3.y && P3.y < pOut->GetHeight() - pOut->GetStatusBarHeight() &&
			P1.x > 0 && P1.x < pOut->GetWidth() && P2.x > 0 && P2.x < pOut->GetWidth() && P3.x > 0 && P3.x < pOut->GetWidth());
	else
		return (pOut->GetToolBarHeight() < P1.y && P1.y < pOut->GetHeight() - pOut->GetStatusBarHeight() && pOut->GetToolBarHeight() < P2.y && P2.y < pOut->GetHeight() - pOut->GetStatusBarHeight() && pOut->GetToolBarHeight() < P3.y && P3.y < pOut->GetHeight() - pOut->GetStatusBarHeight() &&
			P1.x > 0.5*pOut->GetWidth() && P1.x < pOut->GetWidth() && P2.x > 0.5*pOut->GetWidth() && P2.x < pOut->GetWidth() && P3.x >0.5*pOut->GetWidth() && P3.x < pOut->GetWidth());
}



int CFigure::GetID() const
{
	return ID;
}


color CFigure::GetFillColor() const
{
	return FigGfxInfo.FillClr;
}


void CFigure::setFilled(bool isFilled)
{
	FigGfxInfo.isFilled = isFilled;
}


bool CFigure::isFilled()
{
	return FigGfxInfo.isFilled;
}


color CFigure::GetBorderColor() const
{
	return FigGfxInfo.DrawClr;
}