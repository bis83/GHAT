#include "Boss.h"

#include "TaskFactory.h"
#include "MyShip.h"
#include "Config.h"
#include "bgeMath.h"

CBoss3::CBoss3(CHandleGraphics *hGrap, CHandleMedia *hMedi)
{
	Set("Data/Mesh/boss3.x", hGrap);
	vecPos = D3DXVECTOR3(2.4f, 0.0f, 0.0f);
	vecScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	vecRot = D3DXVECTOR3(D3DX_PI/2, D3DX_PI, 0.0f);

	// ìñÇΩÇËîªíË
	hit[0].c = vecPos;
	hit[0].r = 0.3f;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[1].r = 0.25f;
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	hit[2].r = 0.25f;

	life = 400;
	pattern = 0;
	act = 0;
	timer = 0;
	loop = 0;

	shotSoundID[0] = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
	shotSoundID[1] = hMedi->GetMediaObjectID("Data/Media/bullet2.wav");
	shotSoundID[2] = hMedi->GetMediaObjectID("Data/Media/bullet3.wav");
}

CBoss3::~CBoss3()
{
}

bool CBoss3::Update(CHandleMedia *hMedi)
{
	timer++;
	if(loop >= 3)
	{
		// É{ÉXé©îö
		e_taskFactory.CreateExplode(2, vecPos);
		return false;
	}
	switch(pattern)
	{
	case 0:		// ìoèÍ
		vecPos.x -= 0.02f;
		if(timer > 60)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 1:		// é©ã@ë_Ç¢3way
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (60-e_Config.difficult*10) == 59-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<3; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.4f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(D3DX_PI/6-i*D3DX_PI/6+atan2(e_MyShip.vecPos.y-vecPos.y+0.4f, e_MyShip.vecPos.x-vecPos.x+0.5f)),
					(0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/6-i*D3DX_PI/6+atan2(e_MyShip.vecPos.y-vecPos.y+0.4f, e_MyShip.vecPos.x-vecPos.x+0.5f)), 0.0f));
			}
			for(int i=0; i<3; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y+0.4f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(D3DX_PI/6-i*D3DX_PI/6+atan2(e_MyShip.vecPos.y-vecPos.y-0.4f, e_MyShip.vecPos.x-vecPos.x+0.5f)),
					(0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/6-i*D3DX_PI/6+atan2(e_MyShip.vecPos.y-vecPos.y-0.4f, e_MyShip.vecPos.x-vecPos.x+0.5f)), 0.0f));
			}
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 2:		// zako1èoåª
		if(timer % 120 == 119)
		{
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, 0.6f, 0.0f));
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, -0.6f, 0.0f));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 400)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 3:		// ëÂó É~ÉTÉCÉã
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (60-e_Config.difficult*10) == 59-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[1], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[1]);
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y+0.4f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.4f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));

			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.6f, vecPos.y+0.9f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.6f, vecPos.y-0.9f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));

			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.6f, vecPos.y+0.8f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
			e_taskFactory.CreateBullet(2, D3DXVECTOR3(vecPos.x-0.6f, vecPos.y-0.8f, vecPos.z),
				D3DXVECTOR3(-0.04f, 0.0f, 0.0f));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 4:		// zako2èoåª
		if(timer % (160-e_Config.difficult*10) == 159-e_Config.difficult*10)
		{
			e_taskFactory.CreateEnemy(2, 2, D3DXVECTOR3(vecPos.x+0.3f, vecPos.y-0.8f, vecPos.z));
			e_taskFactory.CreateEnemy(2, 2, D3DXVECTOR3(vecPos.x+0.3f, vecPos.y+0.8f, vecPos.z));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 400)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 5:		// ÉâÉìÉ_ÉÄÉoÉãÉJÉì
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % 4 == 3)
		{
			srand(timeGetTime());
			int i = rand()%20 + 1;
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.04f, vecPos.y, vecPos.z),
				D3DXVECTOR3((-0.02f-0.005f*e_Config.difficult)*cos(D3DX_PI/4-i*D3DX_PI/40),
					(0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/4-i*D3DX_PI/40), 0.0f));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 6:		// ëSï˚à 20way+âQä™Ç´íe
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (90-e_Config.difficult*10) == 89-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<20; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y+0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(i*D3DX_PI/6),
					(0.02f+0.005f*e_Config.difficult)*sin(i*D3DX_PI/6), 0.0f));
			}
			for(int i=0; i<20; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y-0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(i*D3DX_PI/6),
					(0.02f+0.005f*e_Config.difficult)*sin(i*D3DX_PI/6), 0.0f));
			}
		}
		if(timer % 4 == 3)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(timer*D3DX_PI/120),
					(0.02f+0.005f*e_Config.difficult)*sin(timer*D3DX_PI/120), 0.0f));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 7:		// zako6èoåª
		if(timer % 150 == 149)
		{
			e_taskFactory.CreateEnemy(6, 1, D3DXVECTOR3(-2.2f, 0.6f, 0.0f));
			e_taskFactory.CreateEnemy(6, 1, D3DXVECTOR3(-2.2f, -0.6f, 0.0f));
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 400)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 8:		// é©ã@ë_Ç¢çÇë¨9way
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer > 60 && timer % 20 == 19)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<9; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
					D3DXVECTOR3(0.1f*cos(2*D3DX_PI/9-i*D3DX_PI/18+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)),
					0.1f*sin(2*D3DX_PI/9-i*D3DX_PI/18+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)), 0.0f));
			}
		}
		if(life <= 100)
		{
			timer = 0;
			pattern = 9;
			act = 0;
			break;
		}
		if(timer > 120)
		{
			timer = 0;
			pattern = 1;
			loop++;
			act = 0;
		}
		break;
	case 9:		// î≠ã∂çUåÇ+zako1èoåª
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (90-e_Config.difficult*10) == 89-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<30; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y+0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(i*D3DX_PI/15),
					(0.02f+0.005f*e_Config.difficult)*sin(i*D3DX_PI/15), 0.0f));
			}
			for(int i=0; i<30; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y-0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(i*D3DX_PI/15),
					(0.02f+0.005f*e_Config.difficult)*sin(i*D3DX_PI/15), 0.0f));
			}
		}
		if(timer % 4 == 3)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y+0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(timer*D3DX_PI/80),
					(0.02f+0.005f*e_Config.difficult)*sin(timer*D3DX_PI/80), 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x, vecPos.y-0.6f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(-timer*D3DX_PI/80),
					(0.02f+0.005f*e_Config.difficult)*sin(-timer*D3DX_PI/80), 0.0f));
		}
		if(timer % 120 == 119)
		{
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, 0.8f, 0.0f));
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, -0.8f, 0.0f));
		}
		if(timer % 100 == 99)
		{
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, 0.4f, 0.0f));
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, -0.4f, 0.0f));
		}
		if(timer > 1200)
		{
			// É{ÉXé©îö
			e_taskFactory.CreateExplode(2, vecPos);
			return false;
		}
		break;
	}
	hit[0].c = vecPos;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	if(life <= 0)
	{
		// É{ÉXåÇîj
		e_taskFactory.CreateExplode(2, vecPos);
		// ìGÇ‚íeÇÃè¡ãé
		e_taskMgr.enemy->ClearTask();
		e_taskMgr.bullet->ClearTask();
		e_MyShip.AddScore(30000);
		return false;
	}
	return true;
}

void CBoss3::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}

bool CBoss3::Hit(CDynamics *target)
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