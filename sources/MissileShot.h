#ifndef MISSILESHOT_H
#define MISSILESHOT_H

#include "Shot.h"
#include "Enemy.h"

//=============================================================
// CMissileShot
//-------------------------------------------------------------
// î≠ê∂éûÇ…ç≈Ç‡ãﬂÇ¢ìGÇïﬂë®ÇµÇƒí«îˆÇ∑ÇÈíeÅB
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
