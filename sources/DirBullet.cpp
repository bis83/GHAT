#include "DirBullet.h"

CDirBullet::CDirBullet(CTaskList *_taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CBullet(_taskList)
{
	Set("Data/Mesh/tama01.x", hGrap);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
	vecScale = D3DXVECTOR3(0.04f, 0.02f, 0.04f);
	hit.c = vecPos;
	hit.r = 0.015f;
	dead = false;
}

CDirBullet::~CDirBullet()
{
}

void CDirBullet::Draw(CHandleGraphics *hGrap) {
	DrawThing(hGrap);
}

bool CDirBullet::Hit(CDynamics *target) {
	return hit.Hit(target);
}

bool CDirBullet::Update() {
	vecPos += vecVel;
	hit.c = vecPos;
	if(OutSurface())
	{
		dead = true;
	}
	return !dead;
}