#ifndef HITBULLET_H
#define HITBULLET_H

#include "Effect.h"

//=============================================================
// CHitBullet
//-------------------------------------------------------------
// 敵への弾のヒット時のエフェクトクラス。
//=============================================================
class CHitBullet : public CEffect
{
public:
	CHitBullet(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos);
	~CHitBullet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
private:
	D3DXVECTOR3 vecOriPos;
	// 乱数固定用シード
	DWORD seed;
	int timer;
};

#endif
