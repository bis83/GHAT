#ifndef BLOCK_H
#define BLOCK_H

#include "Rig.h"

//=============================================================
// CBlock
//-------------------------------------------------------------
// ブロック障害物。
// 破壊されないブロックと破壊可能ブロックがある。
// どちらもショットと敵弾を防ぐ。
//=============================================================
class CBlock : public CRig
{
public:
	CBlock(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel, int type);
	~CBlock();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
	bool Hit(CDynamics *target);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif