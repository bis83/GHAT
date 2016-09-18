#ifndef EQUIP_H
#define EQUIP_H

#include "Effect.h"

//=============================================================
// CEquip
//-------------------------------------------------------------
// 装備取得時のエフェクト。
//=============================================================
class CEquip : public CEffect
{
public:
	CEquip(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CEquip();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// 乱数固定用シード
	DWORD seed;
	int timer;
};

#endif
