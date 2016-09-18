#ifndef SEAFACE_H
#define SEAFACE_H

#include "Back.h"

//=============================================================
// CSeaface
//-------------------------------------------------------------
// äCñ îwåiÅB
//=============================================================
class CSeaface : public CBack, public CThingMesh
{
public:
	CSeaface(CTaskList *taskList, CHandleGraphics *hGrap);
	~CSeaface();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif
