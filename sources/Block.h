#ifndef BLOCK_H
#define BLOCK_H

#include "Rig.h"

//=============================================================
// CBlock
//-------------------------------------------------------------
// �u���b�N��Q���B
// �j�󂳂�Ȃ��u���b�N�Ɣj��\�u���b�N������B
// �ǂ�����V���b�g�ƓG�e��h���B
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