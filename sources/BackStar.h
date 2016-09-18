#ifndef BACKSTAR_H
#define BACKSTAR_H

#include "Back.h"

//=============================================================
// CBackStar
//-------------------------------------------------------------
// 背景の星クラス。
// 3重スクロールぐらいにして見栄えをよくしている。
//=============================================================
class CBackStar : public CBack, public CThingSprite
{
public:
	CBackStar(CTaskList *taskList, CHandleGraphics *hGrap);
	~CBackStar();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	// 乱数シード
	DWORD seed;
	D3DXVECTOR3 vecOriPos;
	int timer;
};

#endif