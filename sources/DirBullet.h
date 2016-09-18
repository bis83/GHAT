#ifndef DIRBULLET_H
#define DIRBULLET_H

#include "Bullet.h"

#include "Dynamics.h"

//=============================================================
// CDirBullet
//-------------------------------------------------------------
// 指定方向に直進する弾。
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
