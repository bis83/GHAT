#include "Boss.h"

#include "MyShip.h"
#include "Config.h"
#include "TaskFactory.h"
#include "bgeMath.h"

CBoss1::CBoss1(CHandleGraphics *hGrap, CHandleMedia *hMedi)
{
	Set("Data/Mesh/boss.x", hGrap);
	vecPos = D3DXVECTOR3(2.5f, 0.0f, 0.0f);
	vecScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	vecRot = D3DXVECTOR3(D3DX_PI/2, D3DX_PI, 0.0f);

	// 当たり判定
	hit[0].c = vecPos;
	hit[0].r = 0.25f;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[1].r = 0.2f;
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	hit[2].r = 0.2f;

	life = 200;
	pattern = 0;
	act = 0;
	timer = 0;
	loop = 0;

	shotSoundID[0] = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
	shotSoundID[1] = hMedi->GetMediaObjectID("Data/Media/bullet2.wav");
	shotSoundID[2] = hMedi->GetMediaObjectID("Data/Media/bullet3.wav");
}

CBoss1::~CBoss1()
{
}

bool CBoss1::Update(CHandleMedia *hMedi)
{
	timer++;
	if(loop >= 3)
	{
		// ボス自爆
		e_taskFactory.CreateExplode(2, vecPos);
		return false;
	}
	switch(pattern)
	{
	case 0:		// 登場
		vecPos.x -= 0.02f;
		if(timer > 50)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 1:		// 3wayバルカン
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (70-e_Config.difficult*10) == 69-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<4; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+0.5f*i, vecPos.z),
					D3DXVECTOR3((-0.02f-0.005f*e_Config.difficult)*cos(D3DX_PI/4), (0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/4), 0.0f));
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+0.5f*i, vecPos.z),
					D3DXVECTOR3(-0.02f-0.005f*e_Config.difficult, 0.0f, 0.0f));
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+0.5f*i, vecPos.z),
					D3DXVECTOR3((-0.02f-0.005f*e_Config.difficult)*cos(D3DX_PI/4), (-0.02f-0.005f*e_Config.difficult)*sin(D3DX_PI/4), 0.0f));
			}
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 2:		// ミサイル
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (160-e_Config.difficult*10) == 159-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[1], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[1]);
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y-0.6f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y+0.6f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 3:		// zako2射出
		if(timer % (160-e_Config.difficult*10) == 159-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[2], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[2]);
			e_taskFactory.CreateEnemy(2, 2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y-0.6f, vecPos.z));
			e_taskFactory.CreateEnemy(2, 2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y+0.6f, vecPos.z));
		}
		if(timer > 400)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 4:		// 自機狙いバルカン+ミサイル
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (120-e_Config.difficult*10) == 119-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<4; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+0.5f*i, vecPos.z),
					MathChangeDirection(D3DXVECTOR3(-0.02f-0.005f*e_Config.difficult, 0.0f, 0.0f), D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+0.5f*i, vecPos.z), e_MyShip.vecPos));
			}
		}
		if(timer % (360-e_Config.difficult*50) == 359-e_Config.difficult*50)
		{
			hMedi->SetPlayStatus(shotSoundID[1], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[1]);
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y-0.6f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x+0.4f, vecPos.y+0.6f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 5:		// zako6出現
		if(timer % 150 == 149)
		{
			e_taskFactory.CreateEnemy(6, 1, D3DXVECTOR3(-2.2f, 0.6f, 0.0f));
			e_taskFactory.CreateEnemy(6, 1, D3DXVECTOR3(-2.2f, -0.6f, 0.0f));
		}
		if(timer > 400)
		{
			timer = 0;
			pattern++;
			if(e_Config.difficult == 1)
			{
				pattern = 1;
				loop++;
			}
			act = 0;
		}
		break;
	case 6:		// 高速ワインダー
		if(timer % (9-e_Config.difficult) == 8-e_Config.difficult)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<2; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.2f+0.5f*i, vecPos.z),
					D3DXVECTOR3(-0.06f*cos(D3DX_PI/6*sin(timer*D3DX_PI/120)), 0.06f*sin(D3DX_PI/6*sin(timer*D3DX_PI/120)), 0.0f));
			}
			for(int i=0; i<2; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.7f+1.5f*i, vecPos.z),
					D3DXVECTOR3(-0.06f, 0.0f, 0.0f));
			}
		}
		if(timer > 300)
		{
			timer = 0;
			pattern = 1;
			act = 0;
			loop++;
		}
		break;
	}
	hit[0].c = vecPos;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	if(life <= 0)
	{
		// ボス撃破
		e_taskFactory.CreateExplode(2, vecPos);
		// 敵や弾の消去
		e_taskMgr.enemy->ClearTask();
		e_taskMgr.bullet->ClearTask();
		e_MyShip.AddScore(30000);
		return false;
	}

	return true;
}

bool CBoss1::Hit(CDynamics *target)
{
	for(int i=0; i<3; i++)
	{
		if(hit[i].Hit(target))
		{
			return true;
		}
	}
	return false;
}

void CBoss1::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
