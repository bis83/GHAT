#ifndef REENTRY_H
#define REENTRY_H

#include "Back.h"

//=============================================================
// CReentry
//-------------------------------------------------------------
// 再突入背景エフェクト。
//=============================================================
class CReentry : public CBack, public CThingSprite {
public:
	CReentry(CTaskList *taskList, CHandleGraphics *hGrap);
	~CReentry();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	DWORD seed;
	int timer;
};

#endif