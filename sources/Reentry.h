#ifndef REENTRY_H
#define REENTRY_H

#include "Back.h"

//=============================================================
// CReentry
//-------------------------------------------------------------
// �ē˓��w�i�G�t�F�N�g�B
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