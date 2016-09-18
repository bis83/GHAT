#ifndef ASTEROID_H
#define ASTEROID_H

#include "Rig.h"

//=============================================================
// CAsteroid
//-------------------------------------------------------------
// 隕石地形。破壊可能。
//=============================================================
class CAsteroid : public CRig
{
public:
	CAsteroid(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CAsteroid();

	bool Update();
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);
	CDynamics* GetDynamics()
	{
		return &hit;
	}
private:
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif