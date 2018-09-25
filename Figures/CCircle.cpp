#include "CCircle.h" 
CCircle::CCircle(Point P1 , double Radius, GfxInfo FigureGfxInfo, int id) :CFigure(FigureGfxInfo, id)
{
	Center = P1;
	radius = Radius;
}


CCircle::CCircle()
{ }

void CCircle::Draw(Output* pOut) const
{
	pOut->Drawcircle(Center,radius, FigGfxInfo,Selected);
}

Point CCircle::GetCenter() const
{
	return Center;
}


bool CCircle::Move(Output* pOut, double X_diff, double Y_diff)
{
	Center.x += X_diff;
	Center.y += Y_diff;
	if (CheckInBoundries(pOut, { Center.x - radius , Center.y - radius }, { Center.x + radius , Center.y + radius }))
		return true;
	else
	{
		Center.x -= X_diff;
		Center.y -= Y_diff;
		return false;
	}
}

bool CCircle::Resize(Output* pOut, float Ratio)
{
	radius *= Ratio;
	if (CheckInBoundries(pOut, { Center.x - radius , Center.y - radius }, { Center.x + radius , Center.y + radius }))
		return true;
	else
	{
		radius /= Ratio;
		return false;
	}
}

void CCircle:: PrintInfo(Output* pOut) 
{
	string Output = "";
	Output += "|| Circle ||  ID: ";
	Output += to_string(ID);
	Output += " Corner1 (";
	Output += to_string((int)Center.x);
	Output += ",";
	Output += to_string((int)Center.y);
	Output += ") Radius : ";
	Output += to_string((int)radius);
	Output += " Borderwidth : ";
	Output += to_string(FigGfxInfo.BorderWdth);
	Output += " Area :";
	Output += to_string((int)GetArea());
	Output += " Perimeter :";
	Output += to_string((int)MYPI * 2 * radius);

	pOut->PrintMessage(Output);

}

bool CCircle::Rotate(Output* pOut, int degrees)
{
	return true;
}

void CCircle::RandomCoordinates(Output* pOut)
{
	srand(time(NULL) + ID);
	do
	{
		Center.x = rand() % ((int)(0.5*pOut->GetWidth() - 2*radius) + 1) + (0.5*pOut->GetWidth() + radius);
		Center.y = rand() % ((pOut->GetHeight() - pOut->GetStatusBarHeight() - (int)(radius) - ( pOut->GetToolBarHeight()+(int)radius) + 1)) + radius + pOut->GetToolBarHeight();
	} while (!CheckInBoundries(pOut, { Center.x - radius , Center.y - radius }, { Center.x + radius , Center.y + radius }, POINTINBOUNDARIES, 0));
}

void CCircle::ResizeHalfLeft()
{
	Center.x = Center.x / 2.0;
	radius = radius / 2.0;
	Center = Center;
	radius = radius;
}

void CCircle::Save(ofstream &OutFile, Output* pOut)
{
	OutFile << "CIRCLE\t";
	OutFile << ID << "\t";
	OutFile << Center.x << "\t" << Center.y << "\t";
	OutFile << radius << "\t";
	OutFile << FigGfxInfo.BorderWdth << "\t";
	OutFile << pOut->GetColorIndex(FigGfxInfo.DrawClr) << "\t";

	if (FigGfxInfo.isFilled)
		OutFile << pOut->GetColorIndex(FigGfxInfo.FillClr) << "\n";
	else
		OutFile << "NO_FILL\n";
}

void CCircle::Load(ifstream &Infile, Output* pOut)
{
	int color; string fill;
	Infile >> ID >> Center.x >> Center.y >> radius >>FigGfxInfo.BorderWdth>> color >> fill;

	FigGfxInfo.DrawClr = FigGfxInfo.DrawClr = pOut->GetColorByIndex(color);

	if (fill == "NO_FILL")
		FigGfxInfo.isFilled = false;
	else
	{
		FigGfxInfo.isFilled = true;
		FigGfxInfo.FillClr=pOut->GetColorByIndex(stoi(fill));
	}

	if (ID > FigureCount)
		FigureCount = ID;
}


bool CCircle::CheckCoordinates(double X, double Y) {
	Point p;
	p.x = X; p.y = Y;
	if ((pow((p.x - Center.x), 2) + pow((p.y - Center.y), 2) <= pow(radius, 2)))
		return true;
	else
		return false;
}

CFigure* CCircle::Copy(bool i)
{
	if (i == true)
		return new CCircle(Center, radius, FigGfxInfo, ID);
	else
		return new CCircle(Center, radius, FigGfxInfo);
}


TYPE CCircle::GetType()
{
	return TCIRCLE;
}

double CCircle::GetArea()
{
	return MYPI * radius * radius;
}

CCircle::~CCircle()
{ }