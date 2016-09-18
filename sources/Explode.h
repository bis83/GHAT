#ifndef EXPLODE_H
#define EXPLODE_H

#include "Effect.h"

//=============================================================
// CExplode
//-------------------------------------------------------------
// 爆発クラス。
// 引数によって爆発の規模を変えることができる。
//=============================================================
class CExplode : public CEffect
{
public:
	CExplode(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int type);
	~CExplode();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// 乱数固定用シード
	DWORD seed;
	int timer;
	int type;
};

#endif
