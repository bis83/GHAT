#include "Asteroid.h"

#include "TaskFactory.h"

CAsteroid::CAsteroid(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CRig(taskList)
{
	Set("Data/Mesh/asteroid.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	this->vecVel = vecVel;
	hit.c = vecPos;
	hit.r = 0.1f;

	life = 10;
	dead = false;
	power = 1;
}

CAsteroid::~CAsteroid()
{
}

bool CAsteroid::Update()
{
	vecPos += vecVel;
	vecRot.z += 0.01f;
	hit.c = vecPos;
	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		dead = true;
	}
	if(OutSurface())
	{
		dead = true;
	}
	return !dead;
}

bool CAsteroid::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CAsteroid::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}