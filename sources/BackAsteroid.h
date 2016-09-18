#ifndef BACKASTEROID_H
#define BACKASTEROID_H

#include "Back.h"

//=============================================================
// CBackAsteroid
//-------------------------------------------------------------
// 背景の隕石群クラス。
// 3重スクロールぐらいにして見栄えをよくしている。
//=============================================================
class CBackAsteroid : public CBack, public CThingSprite
{
public:
	CBackAsteroid(CTaskList *taskList, CHandleGraphics *hGrap);
	~CBackAsteroid();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	// 乱数シード
	DWORD seed;
	D3DXVECTOR3 vecOriPos;
	int timer;
};

#endif