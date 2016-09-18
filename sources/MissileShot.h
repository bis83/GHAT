#ifndef MISSILESHOT_H
#define MISSILESHOT_H

#include "Shot.h"
#include "Enemy.h"

//=============================================================
// CMissileShot
//-------------------------------------------------------------
// 発生時に最も近い敵を捕捉して追尾する弾。
//=============================================================
class CMissileShot : public CShot
{
public:
	CMissileShot(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CMissileShot();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
	bool Hit(CDynamics *target);
	CDynamics *GetDynamics()
	{
		return &hit;
	}
private:
	int timer;
	bool targetDead;
	CEnemy *p_enemy;
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif
