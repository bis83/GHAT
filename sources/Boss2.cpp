#include "Boss.h"

#include "MyShip.h"
#include "Config.h"
#include "TaskFactory.h"
#include "bgeMath.h"

CBoss2::CBoss2(CHandleGraphics *hGrap, CHandleMedia *hMedi)
{
	Set("Data/Mesh/boss2.x", hGrap);
	vecPos = D3DXVECTOR3(2.4f, 0.0f, 0.0f);
	vecScale = D3DXVECTOR3(0.2f, 0.2f, 0.2f);
	vecRot = D3DXVECTOR3(D3DX_PI/2, D3DX_PI, 0.0f);

	// “–‚½‚è”»’è
	hit[0].c = vecPos;
	hit[0].r = 0.28f;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[1].r = 0.2f;
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	hit[2].r = 0.2f;

	life = 300;
	pattern = 0;
	act = 0;
	timer = 0;
	loop = 0;

	char s[] = {1, -9, 2, 8, -6, 5, 3, -4, 4, 7, -2, -7, 9, 0, -1, 6, -8, -3, -5};
	for(int i=0; i<19; i++)
	{
		s_table[i] = s[i];
	}
	s_index = 0;

	shotSoundID[0] = hMedi->GetMediaObjectID("Data/Media/bullet1.wav");
	shotSoundID[1] = hMedi->GetMediaObjectID("Data/Media/bullet2.wav");
	shotSoundID[2] = hMedi->GetMediaObjectID("Data/Media/bullet3.wav");
}

CBoss2::~CBoss2()
{
}

bool CBoss2::Update(CHandleMedia *hMedi)
{
	timer++;
	if(timer % (80-e_Config.difficult*10) == 79-e_Config.difficult*10)
	{
		e_taskFactory.CreateRig(1, D3DXVECTOR3(-2.5f, 0.1f*(s_table[s_index]), 0.0f), D3DXVECTOR3(0.01f, 0.0f, 0.0f));
		s_index++;
		if(s_index > 19)
		{
			s_index = 0;
		}
	}
	if(loop >= 3)
	{
		// ƒ{ƒXŽ©”š
		e_taskFactory.CreateExplode(2, vecPos);
		return false;
	}
	switch(pattern)
	{
	case 0:		// “oê
		vecPos.x -= 0.02f;
		if(timer > 60)
		{
			timer = 0;
			pattern++;
			act = 0;
		}
		break;
	case 1:		// ‘S•ûˆÊ30way
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
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 2:		// Žž‹@‘_‚¢7way
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
			for(int i=0; i<7; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y-0.4f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(D3DX_PI/4-i*D3DX_PI/12+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)),
					(0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/4-i*D3DX_PI/12+atan2(e_MyShip.vecPos.y-vecPos.y,e_MyShip.vecPos.x-vecPos.x)), 0.0f));
			}
			for(int i=0; i<7; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.5f, vecPos.y+0.4f, vecPos.z),
					D3DXVECTOR3((0.02f+0.005f*e_Config.difficult)*cos(D3DX_PI/4-i*D3DX_PI/12+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)),
					(0.02f+0.005f*e_Config.difficult)*sin(D3DX_PI/4-i*D3DX_PI/12+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)), 0.0f));
			}
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 3:		// zako1oŒ»
		if(timer % 120 == 119)
		{
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, 0.6f, 0.0f));
			e_taskFactory.CreateEnemy(1, 4, D3DXVECTOR3(2.4f, -0.6f, 0.0f));
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 4:		// 4wayƒoƒ‹ƒJƒ“+ƒ~ƒTƒCƒ‹
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % 20 == 19)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
				D3DXVECTOR3(-0.04f*cos(D3DX_PI/6), -0.04f*sin(D3DX_PI/6), 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
				D3DXVECTOR3(-0.04f*cos(D3DX_PI/12), -0.04f*sin(D3DX_PI/12), 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
				D3DXVECTOR3(-0.04f*cos(-D3DX_PI/12), -0.04f*sin(-D3DX_PI/12), 0.0f));
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
				D3DXVECTOR3(-0.04f*cos(-D3DX_PI/6), -0.04f*sin(-D3DX_PI/6), 0.0f));
		}
		if(timer % (90-e_Config.difficult*10) == 89-e_Config.difficult*10)
		{
			hMedi->SetPlayStatus(shotSoundID[1], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[1]);
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(D3DX_PI/2), 0.04f*sin(D3DX_PI/2), 0.0f));
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(D3DX_PI/3), 0.04f*sin(D3DX_PI/3), 0.0f));
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(D3DX_PI/4), 0.04f*sin(D3DX_PI/4), 0.0f));
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(-D3DX_PI/4), 0.04f*sin(-D3DX_PI/4), 0.0f));
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(-D3DX_PI/3), 0.04f*sin(-D3DX_PI/3), 0.0f));
			e_taskFactory.CreateBullet(2, vecPos, D3DXVECTOR3(-0.04f*cos(-D3DX_PI/2), 0.04f*sin(-D3DX_PI/2), 0.0f));
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 5:		// zako5oŒ»
		if(timer % 100 == 99)
		{
			e_taskFactory.CreateEnemy(5, 2, D3DXVECTOR3(-1.2f, 1.6f, 0.0f));
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 6:		// ‚‘¬Žž‹@‘_‚¢’e+‘S•ûˆÊ20way
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % (110-e_Config.difficult*20) == 109-e_Config.difficult*20)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
				MathChangeDirection(D3DXVECTOR3(-0.08f, 0.0f, 0.0f), vecPos, e_MyShip.vecPos));
		}
		if(timer % (120-e_Config.difficult*10) == 119-e_Config.difficult*10)
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
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			act++;
		}
		break;
	case 7:		// zako2ŽËo
		if(timer % 70 == 69)
		{
			hMedi->SetPlayStatus(shotSoundID[2], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[2]);
			e_taskFactory.CreateEnemy(2, 2, vecPos);
		}
		if(timer > 300)
		{
			timer = 0;
			pattern++;
			if(e_Config.difficult == 1)
			{
				pattern = 1;
				loop++;
			}
			act++;
		}
		break;
	case 8:		// Žž‹@‘_‚¢‚‘¬21way
		if(fabs(vecPos.y - e_MyShip.vecPos.y) > 0.1f)
		{
			if(vecPos.y > e_MyShip.vecPos.y)
			{
				vecPos.y -= 0.01f;
			} else {
				vecPos.y += 0.01f;
			}
		}
		if(timer % 20 == 19)
		{
			hMedi->SetPlayStatus(shotSoundID[0], MOS_VOLUME, &e_Config.se_volume);
			hMedi->PlaySE(shotSoundID[0]);
			for(int i=0; i<21; i++)
			{
				e_taskFactory.CreateBullet(1, D3DXVECTOR3(vecPos.x-0.3f, vecPos.y, vecPos.z),
					D3DXVECTOR3(0.1f*cos(D3DX_PI/3-i*D3DX_PI/30+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)),
					0.1f*sin(D3DX_PI/3-i*D3DX_PI/30+atan2(e_MyShip.vecPos.y-vecPos.y, e_MyShip.vecPos.x-vecPos.x)), 0.0f));
			}
		}
		if(timer > 60)
		{
			timer = 0;
			pattern = 1;
			loop++;
			act++;
		}
		break;
	}
	hit[0].c = vecPos;
	hit[1].c = D3DXVECTOR3(vecPos.x, vecPos.y+0.5f, vecPos.z);
	hit[2].c = D3DXVECTOR3(vecPos.x, vecPos.y-0.5f, vecPos.z);
	if(life <= 0)
	{
		// ƒ{ƒXŒ‚”j
		e_taskFactory.CreateExplode(2, vecPos);
		// “G‚â’e‚ÌÁ‹Ž
		e_taskMgr.enemy->ClearTask();
		e_taskMgr.bullet->ClearTask();
		e_MyShip.AddScore(30000);
		return false;
	}
	return true;
}

bool CBoss2::Hit(CDynamics *target)
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

void CBoss2::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}
