#include "MissileShot.h"

#include "TaskFactory.h"
#include "bgeMath.h"

#include "Config.h"

CMissileShot::CMissileShot(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CShot(taskList)
{
	Set("Data/Mesh/tama02.x", hGrap);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
	vecScale = D3DXVECTOR3(0.06f, 0.06f, 0.06f);
	hit.c = vecPos;
	hit.r = 0.015f;

	power = 3;
	shotType = 2;
	dead = false;
	targetDead = false;
	p_enemy = NULL;
	timer = 0;

	// 最も近い敵へのポインタを取得
	CEnemy *t = NULL;
	float len = 999.0f;
	float tl;
	for(CTaskIter i(e_taskMgr.enemy); i.HasNext();)
	{
		t = (CEnemy*)i.Next();
		tl = MathDirection(vecPos, t->vecPos);
		if(len > tl)
		{
			p_enemy = t;
		}
	}

	int seID;
	seID = hMedi->GetMediaObjectID("Data/Media/shot.wav");
	hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
	hMedi->PlaySE(seID);
}

CMissileShot::~CMissileShot()
{
}

bool CMissileShot::Update()
{
	// ターゲットが死んでいるか判定
	if(p_enemy == NULL || p_enemy->IsDead())
	{
		targetDead = true;
	}

	timer++;
	if(timer < 300 && timer%6 == 0 && !targetDead)
	{
		D3DXVECTOR3 vecTar = MathChangeDirection(vecVel, vecPos, p_enemy->vecPos);
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
		if(theta > D3DX_PI/4)
		{
			vecVel = D3DXVECTOR3(len*cos(atan2(vecVel.y, vecVel.x)+D3DX_PI/4),
				len*sin(atan2(vecVel.y, vecVel.x)+D3DX_PI/4), vecVel.z);
		} else if(theta < -D3DX_PI/4)
		{
			vecVel = D3DXVECTOR3(len*cos(atan2(vecVel.y, vecVel.x)-D3DX_PI/4),
				len*sin(atan2(vecVel.y, vecVel.x)-D3DX_PI/4), vecVel.z);
		} else {
			vecVel = vecTar;
		}
		vecRot = D3DXVECTOR3(0.0f, 0.0f, atan2(vecVel.y, vecVel.x));
	}
	if(timer % 6 == 5)
	{
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

bool CMissileShot::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CMissileShot::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
