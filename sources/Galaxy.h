#ifndef GALAXY_H
#define GALAXY_H

#include "Back.h"

#include "Back.h"

//=============================================================
// CGalaxy
//-------------------------------------------------------------
// âFíàîwåiópÅB
//=============================================================
class CGalaxy : public CBack, public CThingSprite
{
public:
	CGalaxy(CTaskList *taskList, CHandleGraphics *hGrap);
	~CGalaxy();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif
