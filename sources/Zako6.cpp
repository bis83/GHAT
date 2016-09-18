#include "Zako.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "bgeMath.h"
#include "Config.h"

CZako6::CZako6(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako6.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	vecRot = D3DXVECTOR3(D3DX_PI/2, D3DX_PI, 0.0f);
	hit.c = vecPos;
	hit.r = 0.1f;

	enemyID = 6;
	life = 8;
	pattern = action;
	act = 0;
	switch(pattern)
	{
	case 1:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.02f : -0.02f), 0.0f, 0.0f);
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	case 2:
		vecVel = D3DXVECTOR3(0.0f, (vecPos.y < 0 ? 0.02f : -0.02f), 0.0f);
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	}
	timer = 0;
	dead = false;
	shotSoundID = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
}

CZako6::~CZako6()
{
}

bool CZako6::Update(CHandleMedia *hMedi)
{
	timer++;
	switch(pattern)
	{
	case 1:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 40)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 120)
			{
				vecVel.x *= -1.0f;
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecPos += vecVel;
			if(timer < 31)
			{
				vecRot.y += D3DX_PI/30;
			}
			break;
		}
		break;
	case 2:
		vecPos += vecVel;
		if(fabs(vecPos.y) < 1.2f)
		{
			Shot(hMedi);
		}
		break;
	}

	hit.c = vecPos;

	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		e_MyShip.AddScore(400);
		Dead();
	}
	if(OutSurface())
	{
		Dead();
	}
	return !dead;
}

void CZako6::Shot(CHandleMedia *hMedi)
{
	if(timer % (90-e_Config.difficult*10) == 89-e_Config.difficult*10)
	{
		float o = vecRot.y < D3DX_PI ? -1.0f : 1.0f;
		for(int i=0; i<2; i++)
		{
			hMedi->SetPlayStatus(shotSoundID, MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-o*0.2f, vecPos.y-0.08f+0.16f*i, vecPos.z),
				D3DXVECTOR3(-0.01f*o*(2.0f+0.5f*e_Config.difficult)*cos(D3DX_PI/4), 0.01f*o*(2.0f+0.5f*e_Config.difficult)*sin(D3DX_PI/4), 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-o*0.2f, vecPos.y-0.08f+0.16f*i, vecPos.z),
				D3DXVECTOR3(-0.01f*o*(2.0f+0.5f*e_Config.difficult), 0.0f, 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-o*0.2f, vecPos.y-0.08f+0.16f*i, vecPos.z),
				D3DXVECTOR3(-0.01f*o*(2.0f+0.5f*e_Config.difficult)*cos(D3DX_PI/4), -0.01f*o*(2.0f+0.5f*e_Config.difficult)*sin(D3DX_PI/4), 0.0f));
		}
	}
}

bool CZako6::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako6::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
