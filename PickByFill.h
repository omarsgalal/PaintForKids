#pragma once
#include "Actions\Action.h"
class PickByFill :
	public Action
{
	bool Found,Filled, TemporaryFilled;
	int Valid, InValid, Count, Grade;
	color FillColor, TemporaryFillColor;
public:
	PickByFill(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual bool Execute();
	~PickByFill();
};

