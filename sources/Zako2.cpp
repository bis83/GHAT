#include "Zako.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "Config.h"
#include "bgeMath.h"

CZako2::CZako2(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako2.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
	vecRot = D3DXVECTOR3(0.0f, D3DX_PI, 0.0f);
	hit.c = vecPos;
	hit.r = 0.15f;

	enemyID = 2;
	life = 2;
	pattern = action;
	act = 0;
	switch(pattern)
	{
	case 1:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.02f : -0.02f), 0.0f, 0.0f);
		break;
	case 2:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.03f : -0.03f), 0.0f, 0.0f);
		break;
	case 3:
		vecVel = D3DXVECTOR3(0.0f, (vecPos.y < 0 ? 0.01f : -0.01f), 0.0f);
		break;
	case 4:
		vecVel = D3DXVECTOR3(0.04f, 0.0f, 0.0f);
		break;
	}

	timer = 0;
	dead = false;
	shotSoundID = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
}

CZako2::~CZako2()
{
}

bool CZako2::Update(CHandleMedia *hMedi)
{
	timer++;
	switch(pattern)
	{
	case 1:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 60)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 180)
			{
				timer = 0;
				act++;
				vecVel.x *= 2.0f;
				vecVel = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
			}
			break;
		case 2:
			vecPos += vecVel;
			break;
		}
		break;
	case 2:
		vecPos += vecVel;
		Shot(hMedi);
		break;
	case 3:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 60)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 180)
			{
				timer = 0;
				act++;
				vecVel.y *= 4.0f;
				vecVel = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
			}
			break;
		case 2:
			vecPos += vecVel;
			break;
		}
		break;
	case 4:
		switch(act)
		{
		case 0:
			vecVel = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
			vecPos += vecVel;
			if(MathDirection(vecPos, e_MyShip.vecPos) < 0.5f)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 180)
			{
				vecVel = D3DXVECTOR3(-0.04f, 0.0f, 0.0f);
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecPos += vecVel;
			break;
		}
		break;
	}
	hit.c = vecPos;
	vecRot.z += D3DX_PI / 40.0f;

	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		e_MyShip.AddScore(200);
		Dead();
	}
	return !dead;
}

void CZako2::Shot(CHandleMedia *hMedi)
{
	if(timer % (66-e_Config.difficult*10) == 65-e_Config.difficult*10)
	{
		for(int i=0; i<4; i++)
		{
			hMedi->SetPlayStatus(shotSoundID, MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID);
			e_taskFactory.CreateBullet(1, vecPos, D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(-vecRot.z+D3DX_PI/4+i*D3DX_PI/2),
				(0.02f+0.005f*e_Config.difficult)*sin(-vecRot.z+D3DX_PI/4+i*D3DX_PI/2), 0.0f));
		}
	}
}

bool CZako2::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako2::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
