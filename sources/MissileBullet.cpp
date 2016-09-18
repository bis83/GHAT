#include "MissileBullet.h"

#include "MyShip.h"
#include "bgeMath.h"
#include "TaskFactory.h"

CMissileBullet::CMissileBullet(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CBullet(taskList)
{
	Set("Data/Mesh/tama02.x", hGrap);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
	vecScale = D3DXVECTOR3(0.06f, 0.06f, 0.06f);
	hit.c = vecPos;
	hit.r = 0.015f;
	dead = false;
	timer = 0;
}

CMissileBullet::~CMissileBullet()
{
}

bool CMissileBullet::Update()
{
	timer++;
	if(timer < 300 && timer%6 == 0)
	{
		D3DXVECTOR3 vecTar = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
		float theta = atan2(vecTar.y, vecTar.x) - atan2(vecVel.y, vecVel.x);
		float len = sqrt(vecVel.x*vecVel.x + vecVel.y*vecVel.y);
		if(fabs(theta) > D3DX_PI)
		{
			if(theta > 0)
			{
				theta = theta - 2*D3DX_PI;
			} else {
				theta = 2*D3DX_PI + theta;
			}
		}
		if(theta > D3DX_PI/24)
		{
			vecVel = D3DXVECTOR3(len*cos(atan2(vecVel.y, vecVel.x)+D3DX_PI/24),
				len*sin(atan2(vecVel.y, vecVel.x)+D3DX_PI/24), vecVel.z);
		} else if(theta < -D3DX_PI/24)
		{
			vecVel = D3DXVECTOR3(len*cos(atan2(vecVel.y, vecVel.x)-D3DX_PI/24),
				len*sin(atan2(vecVel.y, vecVel.x)-D3DX_PI/24), vecVel.z);
		} else {
			vecVel = vecTar;
		}
		vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
		e_taskFactory.CreateMissileSmoke(vecPos);
	}
	vecPos += vecVel;
	hit.c = vecPos;

	if(OutSurface())
	{
		dead = true;
	}
	return !dead;
}

bool CMissileBullet::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CMissileBullet::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
