#ifndef SKY_H
#define SKY_H

#include "Back.h"

#include "Back.h"

//=============================================================
// CSky
//-------------------------------------------------------------
// ��w�i�p�B
//=============================================================
class CSky : public CBack, public CThingSprite
{
public:
	CSky(CTaskList *taskList, CHandleGraphics *hGrap);
	~CSky();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif
