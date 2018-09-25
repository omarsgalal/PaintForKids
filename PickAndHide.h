#pragma once
#include "Actions\Action.h"
class PickAndHide :
	public Action
{
	Action* PickMode;
public:
	PickAndHide(ApplicationManager* pApp);
	~PickAndHide();
};

