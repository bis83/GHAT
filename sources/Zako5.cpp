#include "Zako.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "bgeMath.h"
#include "Config.h"

CZako5::CZako5(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako5.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	vecRot = D3DXVECTOR3(D3DX_PI/2, D3DX_PI, 0.0f);
	hit.c = vecPos;
	hit.r = 0.14f;

	enemyID = 5;
	life = 4;
	switch(action)
	{
	case 1:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.01f : -0.01f), 0.0f, 0.0f);
		break;
	case 2:
		vecVel = D3DXVECTOR3(0.0f, (vecPos.y < 0 ? 0.01f : -0.01f), 0.0f);
		break;
	}

	timer = 0;
	dead = false;
	shotSoundID = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
}

CZako5::~CZako5()
{
}

bool CZako5::Update(CHandleMedia *hMedi)
{
	timer++;
	if(vecPos.x < 2.0f && vecPos.x > -2.0f && vecPos.y < 1.0f && vecPos.y > -1.0f)
	{
		if(timer % (100-e_Config.difficult*10) == 99-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID, MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID);
			e_taskFactory.CreateBullet(1, vecPos,
				MathChangeDirection(D3DXVECTOR3(-0.02f-0.005f*e_Config.difficult, 0.0f, 0.0f), vecPos, e_MyShip.vecPos));
		}
	}

	vecPos += vecVel;
	hit.c = vecPos;

	vecRot.x += D3DX_PI/120.0f;
	D3DXVECTOR3 vec = MathChangeDirection(D3DXVECTOR3(1.0f, 0.0f, 0.0f), vecPos, e_MyShip.vecPos);
	vecRot.z = atan2(vec.y, vec.x);

	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		e_MyShip.AddScore(150);
		Dead();
	}
	if(OutSurface())
	{
		Dead();
	}
	return !dead;
}

bool CZako5::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako5::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
