#ifndef FORTBACK_H
#define FORTBACK_H

#include "Back.h"

//=============================================================
// CFortBack
//-------------------------------------------------------------
// 要塞ステージ背景。
//=============================================================
class CFortBack : public CBack, public CThingSprite
{
public:
	CFortBack(CTaskList *taskList, CHandleGraphics *hGrap);
	~CFortBack();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	int timer;
};

#endif