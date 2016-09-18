#ifndef MISSILEBULLET_H
#define MISSILEBULLET_H

#include "Bullet.h"

//=============================================================
// CMissileBullet
//-------------------------------------------------------------
// é©ã@Çïﬂë®ÇµÇƒí«îˆÇ∑ÇÈíeÅB
//=============================================================
class CMissileBullet : public CBullet
{
public:
	CMissileBullet(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CMissileBullet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
	bool Hit(CDynamics *target);
private:
	int timer;
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif
