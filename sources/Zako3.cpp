#include "Zako.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "Config.h"

CZako3::CZako3(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako3.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);
	vecRot = D3DXVECTOR3(D3DX_PI/4, D3DX_PI, 0.0f);
	hit.c = vecPos;
	hit.r = 0.1f;

	enemyID = 3;
	life = 4;
	pattern = action;
	act = 0;
	switch(pattern)
	{
	case 1:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.01f : -0.01f), 0.0f, 0.0f);
		vecRot.x = vecPos.x < 0 ? -D3DX_PI/4 : D3DX_PI/4;
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	case 2:
		vecVel = D3DXVECTOR3(0.0f, (vecPos.y < 0 ? 0.02f : -0.02f), 0.0f);
		vecRot.x = vecPos.x < 0 ? -D3DX_PI/4 : D3DX_PI/4;
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	case 3:
		vecVel = D3DXVECTOR3((vecPos.x < 0 ? 0.01f : -0.01f), 0.0f, 0.0f);
		vecRot.x = vecPos.x < 0 ? -D3DX_PI/4 : D3DX_PI/4;
		vecRot.y = vecPos.x < 0 ? 0.0f : D3DX_PI;
		break;
	}
	timer = 0;
	dead = false;
	shotSoundID = hMedi->GetMediaObjectID("Data/Media/bullet2.wav");
}

CZako3::~CZako3()
{
}

bool CZako3::Update(CHandleMedia *hMedi)
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
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecVel.x *= 1.02f;
			vecRot.x += D3DX_PI/40.0f;
			vecPos += vecVel;
			break;
		}
		break;
	case 2:
		switch(act)
		{
		case 0:
			vecPos += vecVel;
			if(timer > 30)
			{
				vecVel.y /= 2.0f;
				timer = 0;
				act++;
			}
			break;
		case 1:
			vecPos += vecVel;
			Shot(hMedi);
			if(timer > 120)
			{
				vecVel.y *= 2.0f;
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecPos += vecVel;
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
			if(timer > 90)
			{
				timer = 0;
				act++;
			}
			break;
		case 2:
			vecVel.x *= 1.02f;
			vecRot.x += D3DX_PI/40.0f;
			vecPos += vecVel;
			break;
		}
		break;
	}

	// ìñÇΩÇËîªíËÇÃê›íË
	hit.c = vecPos;

	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		e_MyShip.AddScore(300);
		Dead();
	}
	if(OutSurface())
	{
		Dead();
	}
	return !dead;
}

void CZako3::Shot(CHandleMedia *hMedi)
{
	if(timer % 80-e_Config.difficult*10 == 79-e_Config.difficult*10)
	{
		hMedi->SetPlayStatus(shotSoundID, MOS_VOLUME, &e_Config.se_volume);
		hMedi->PlaySE(shotSoundID);
		e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3((vecRot.y < D3DX_PI ? 0.04f : -0.04f), 0.0f, 0.0f));
	}
}

bool CZako3::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako3::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}