#include "Zako.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "Config.h"

CZako1::CZako1(CTaskList *taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, int action)
: CEnemy(taskList)
{
	Set("Data/Mesh/zako1.x", hGrap);
	this->vecPos = vecPos;
	vecScale = D3DXVECTOR3(0.08f, 0.08f, 0.08f);
	hit.c = vecPos;
	hit.r = 0.1f;

	enemyID = 1;
	life = 2;

	pattern = action;
	switch(pattern)
	{
	case 1:
		vecRot = D3DXVECTOR3(D3DX_PI/4, D3DX_PI, 0.0f);
		vecVel = D3DXVECTOR3(-0.02f, 0.0f, 0.0f);
		break;
	case 2:
		vecRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vecVel = D3DXVECTOR3(0.04f, 0.0f, 0.0f);
		break;
	case 3:
		vecRot = D3DXVECTOR3(D3DX_PI/4, D3DX_PI, 0.0f);
		vecVel = D3DXVECTOR3(-0.02f, (vecPos.y < 0 ? 0.02f : -0.02f), 0.0f);
		break;
	case 4:
		vecRot = D3DXVECTOR3(D3DX_PI/4, D3DX_PI, 0.0f);
		vecVel = D3DXVECTOR3(-0.04f, 0.0f, 0.0f);
		break;
	}
	act = 0;
	timer = 0;
	dead = false;
	shotSoundID = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
}

CZako1::~CZako1()
{
}

bool CZako1::Update(CHandleMedia *hMedi)
{
	timer++;
	switch(pattern)
	{
	case 1:
		switch(act)
		{
		case 0:		// 左に低速移動
			vecPos += vecVel;
			if(timer > 90)
			{
				vecVel = D3DXVECTOR3(0.02f*cos(D3DX_PI/4), ((vecPos.y < 0) ? 0.02f : -0.02f)*sin(D3DX_PI/4), 0.0f);
				timer = 0;
				act++;
			}
			Shot(hMedi);
			break;
		case 1:		// ピッチ移動
			vecPos += vecVel;
			vecRot.x += D3DX_PI/30;
			if(timer > 60)
			{
				timer = 0;
				vecVel = D3DXVECTOR3(-0.02f, 0.0f, 0.0f);
				vecRot.x = D3DX_PI/4;
				act++;
			}
			Shot(hMedi);
			break;
		case 2:		// 左に移動2
			vecPos += vecVel;
			Shot(hMedi);
			break;
		}
		break;
	case 2:
		switch(act)
		{
		case 0:		// 高速で右に移動
			vecPos += vecVel;
			if(timer > 90)
			{
				timer = 0;
				act++;
			}
			break;
		case 1:		// ヨー回転
			vecRot.x += D3DX_PI/120;
			vecRot.y += D3DX_PI/30;
			if(timer > 30)
			{
				timer = 0;
				vecRot.x = D3DX_PI/4;
				vecRot.y = D3DX_PI;
				vecVel = D3DXVECTOR3(-0.02f, 0.0f, 0.0f);
				act++;
			}
			break;
		case 2:		// 左へ
			vecPos += vecVel;
			Shot(hMedi);
			break;
		}
		break;
	case 3:
		switch(act)
		{
		case 0:		// 上下にピッチ
			vecRot.x += D3DX_PI/30;
			if(vecVel.x < 0)
			{
				vecVel.x += 0.0003f;
			}
			vecPos += vecVel;
			if(timer > 60)
			{
				timer = 0;
				vecRot.x = D3DX_PI/4;
				vecVel = D3DXVECTOR3(-0.02f, 0.0f, 0.0f);
				act++;
			}
			break;
		case 1:		// 左に移動
			vecPos += vecVel;
			Shot(hMedi);
			break;
		}
		break;
	case 4:
		vecPos += vecVel;
		Shot(hMedi);
		break;
	}

	// 当たり判定の設定
	hit.c = vecPos;

	// 死亡判定
	if(!(life > 0))
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

void CZako1::Shot(CHandleMedia *hMedi)
{
	if(timer % (120-e_Config.difficult*10) == 119-e_Config.difficult*10)
	{
		hMedi->SetPlayStatus(shotSoundID, MOS_VOLUME, &e_Config.se_volume);
		hMedi->PlaySE(shotSoundID);
		e_taskFactory.CreateBullet(1, vecPos, D3DXVECTOR3(-0.02f-0.005f*e_Config.difficult, 0.0f, 0.0f));
	}
}

bool CZako1::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

void CZako1::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
