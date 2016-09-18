#ifndef ITEMGET_H
#define ITEMGET_H

#include "Effect.h"

//=============================================================
// CItemGet
//-------------------------------------------------------------
// アイテム取得時のエフェクトクラス。
//=============================================================
class CItemGet : public CEffect
{
public:
	CItemGet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CItemGet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// 乱数固定用シード
	DWORD seed;
	int timer;
};

#endif
