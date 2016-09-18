#include "Zako.h"

#include "TaskFactory.h"
#include "bgeMath.h"
#include "MyShip.h"
#include "Config.h"

CZako4::CZako4(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako4.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	vecRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	hit.c = vecPos;
	hit.r = 0.08f;

	enemyID = 4;
	life = 10;
	pattern = action;
	act = 0;
	switch(pattern)
	{
	case 1:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.01f : -0.01f), 0.0f, 0.0f);
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	case 2:
		vecVel = D3DXVECTOR3(0.0f, (vecPos.y < 0 ? 0.01f : -0.01f), 0.0f);
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	case 3:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.01f : -0.01f), 0.0f, 0.0f);
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	}
	timer = 0;
	dead = false;
	shotSoundID[0] = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
	shotSoundID[1] = hMedi->GetMediaObjectID("Data/Media/bullet2.wav");
}

CZako4::~CZako4()
{
}

bool CZako4::Update(CHandleMedia *hMedi)
{
	timer++;
	switch(pattern)
	{
	case 1:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 90)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 180)
			{
				if(vecPos.y > 0)
				{
					vecVel = D3DXVECTOR3(0.0f, 0.01f, 0.0f);
				} else {
					vecVel = D3DXVECTOR3(0.0f, -0.01f, 0.0f);
				}
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecPos += vecVel;
			vecRot.x += vecVel.y * 2.0f * D3DX_PI;
			break;
		}
		break;
	case 2:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			vecRot.x += D3DX_PI/30.0f;
			if(timer > 60)
			{
				vecRot.x = 0.0f;
				timer = 0;
				act++;
			}
			break;
		case 1:
			Shot(hMedi);
			if(timer > 180)
			{
				vecVel.y *= 4.0f;
				vecVel = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
				vecRot.z = atan2(vecPos.y - e_MyShip.vecPos.y, vecPos.x - e_MyShip.vecPos.x);
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecPos += vecVel;
			if(timer % 6 == 1)
			{
				e_taskFactory.CreateMissileSmoke(vecPos);
			}
			break;
		}
		break;
	case 3:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 90)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:
			if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
			{
				if(vecPos.y > e_MyShip.vecPos.y)
				{
					vecPos.y -= 0.01f;
				} else {
					vecPos.y += 0.01f;
				}
			}
			Shot(hMedi);
			if(timer > 180)
			{
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecVel *= 1.02f;
			vecPos += vecVel;
			vecRot.x += D3DX_PI/40.0f;
			break;
		}
		break;
	}

	hit.c = vecPos;

	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		e_MyShip.AddScore(500);
		Dead();
	}
	if(OutSurface())
	{
		Dead();
	}
	return !dead;
}

void CZako4::Shot(CHandleMedia *hMedi)
{
	float o = vecRot.y < D3DX_PI ? 0.01f : -0.01f;
	if(timer % (180-e_Config.difficult*10) == 179-e_Config.difficult*10)
	{
		hMedi->SetPlayStatus(shotSoundID[1], MOS_VOLUME, &e_Config.se_volume);
		hMedi->PlaySE(shotSoundID[1]);
		e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(4*o*cos(D3DX_PI/4), -4*o*sin(D3DX_PI/4), 0.0f));
		e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(4*o*cos(D3DX_PI/4), 4*o*sin(D3DX_PI/4), 0.0f));
	}
	if(timer % (120-e_Config.difficult*20) == 119-e_Config.difficult*20)
	{
		hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
		hMedi->PlaySE(shotSoundID[0]);
		e_taskFactory.CreateBullet(1, vecPos, D3DXVECTOR3(o*(2.0f+e_Config.difficult*0.5f)*cos(D3DX_PI/6), -o*(2.0f+e_Config.difficult*0.5f)*sin(D3DX_PI/6), 0.0f));
		e_taskFactory.CreateBullet(1, vecPos, D3DXVECTOR3(o*(2.0f+e_Config.difficult*0.5f), 0.0f, 0.0f));
		e_taskFactory.CreateBullet(1, vecPos, D3DXVECTOR3(o*(2.0f+e_Config.difficult*0.5f)*cos(D3DX_PI/6), o*(2.0f+e_Config.difficult*0.5f)*sin(D3DX_PI/6), 0.0f));
	}
}

bool CZako4::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako4::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
