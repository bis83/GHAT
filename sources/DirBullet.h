#ifndef DIRBULLET_H
#define DIRBULLET_H

#include "Bullet.h"

#include "Dynamics.h"

//=============================================================
// CDirBullet
//-------------------------------------------------------------
// éwíËï˚å¸Ç…íºêiÇ∑ÇÈíeÅB
//=============================================================
class CDirBullet : public CBullet
{
public:
	CDirBullet(CTaskList *_taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CDirBullet();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
	bool Hit(CDynamics *target);
private:
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif
