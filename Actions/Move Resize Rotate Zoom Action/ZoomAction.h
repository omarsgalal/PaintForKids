#ifndef ZOOM_ACTION_H
#define ZOOM_ACTION_H

#include "..\Action.h"
#include "..\..\ApplicationManager.h"

class ZoomAction : public Action
{
	float ZoomFactor;
public:
	ZoomAction(ApplicationManager *pApp);

	virtual void ReadActionParameters();

	virtual bool Execute(ActionType *&);

	virtual ~ZoomAction();

};
#endif	