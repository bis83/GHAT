#ifndef FORTBACK_H
#define FORTBACK_H

#include "Back.h"

//=============================================================
// CFortBack
//-------------------------------------------------------------
// �v�ǃX�e�[�W�w�i�B
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