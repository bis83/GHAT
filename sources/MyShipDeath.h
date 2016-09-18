#ifndef MYSHIPDEATH_H
#define MYSHIPDEATH_H

#include "Effect.h"

//=============================================================
// CMyShipDeath
//-------------------------------------------------------------
// 自機の死亡時の爆発エフェクト。
//=============================================================
class CMyShipDeath : public CEffect
{
public:
	CMyShipDeath(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CMyShipDeath();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// 乱数固定用シード
	DWORD seed;
	int timer;
};

#endif
