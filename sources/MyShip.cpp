#include "MyShip.h"

#include "TaskManager.h"
#include "TaskFactory.h"
#include "Config.h"

#include "MyShipDeath.h"

#include "Item.h"

CMyShip::CMyShip()
: CThingMesh()
{
}

void CMyShip::Init(CHandleGraphics *hGrap)
{
	// グラフィックの取得
	Set("Data/Mesh/ghat.x", hGrap);
	weaponGrapID[0] = objectID;
	weaponGrapID[1] = hGrap->GetDrawObjectID("Data/Mesh/zako1.x");
	weaponGrapID[2] = hGrap->GetDrawObjectID("Data/Mesh/zako2.x");
	weaponGrapID[3] = hGrap->GetDrawObjectID("Data/Mesh/zako3.x");
	weaponGrapID[4] = hGrap->GetDrawObjectID("Data/Mesh/zako4.x");
	weaponGrapID[5] = hGrap->GetDrawObjectID("Data/Mesh/zako5.x");
	weaponGrapID[6] = hGrap->GetDrawObjectID("Data/Mesh/zako6.x");
	// 各種ステータスをセット
	score = 0;
	restShip = e_Config.rest;
	shipType = 0;
	weaponID = 0;
	tentacle = false;
	gathering = false;
	g_charge = 0;
	t_charge = 0;
	restShot = 0;
	dead = true;
	hitRange.r = 0.00f;
	itemCollectRange.r = 0.2f;
	lastMoveRad = 0.0f;

	// 初期位置をセット
	vecPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vecScale = D3DXVECTOR3(0.1f, 0.1f, 0.1f);

	// 無敵時間をセット
	blink = 120;
}

void CMyShip::Update(int a, int b, int anaX, int anaY, CHandleMedia *hMedi)
{
	// 無敵時間の経過
	if(blink > 0)
	{
		blink--;
	}
	// 死亡フラグがたっている場合は死亡する
	if(dead)
	{
		Revive();
		return;
	}

	// 移動
	if(abs(anaX) > 500 || abs(anaY) > 500)
	{
		lastMoveRad = atan2((float)anaY, (float)anaX);
		vecPos.x += 0.02f * cos(lastMoveRad);
		vecPos.y += -0.02f * sin(lastMoveRad);
	}
	if(anaY > 500) 
	{
		vecRot.x -= 0.1f;
		if(vecRot.x < -0.3f)
		{
			vecRot.x = -0.3f;
		}
	} else if(anaY < -500) {
		vecRot.x += 0.1f;
		if(vecRot.x > 0.3f)
		{
			vecRot.x = 0.3f;
		}
	}
	if(abs(anaY) < 500)
	{
		if(vecRot.x >= 0.1f)
		{
			vecRot.x -= 0.1f;
		} else if(vecRot.x <= -0.1f)
		{
			vecRot.x += 0.1f;
		}
	}
	// 上限下限
	if(vecPos.x > 2.0f)
	{
		vecPos.x = 2.0f;
	}
	if(vecPos.x < -2.0f)
	{
		vecPos.x = -2.0f;
	}
	if(vecPos.y > 1.1f)
	{
		vecPos.y = 1.1f;
	}
	if(vecPos.y < -1.1f)
	{
		vecPos.y = -1.1f;
	}

	// 当たり判定の位置を修正
	hitRange.c = vecPos;
	itemCollectRange.c = vecPos;
	
	if(a == 0)
	{
		g_charge++;
		if(g_charge > 60)
		{
			gathering = true;
		} else {
			gathering = false;
		}
	} else {
		g_charge = 0;
		gathering = false;
	}

	// ショットボタンを押している場合はショットを行う
	if(weaponID == 0)
	{
		if(t_charge > 30)
		{
			// チャージ完了の音を出す
			if(!tentacle)
			{
				e_taskFactory.CreateEquipEffect(vecPos);
				tentacle = true;
			}
			if(a % 3 == 1)
			{
				int seID = hMedi->GetMediaObjectID("Data/Media/charge.wav");
				int f = 5000 * (a%6+1);
				hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
				hMedi->SetPlayStatus(seID, MOS_FREQUENCY, &f);
				hMedi->PlaySE(seID);
			}
		} else if(t_charge > 0)
		{
			// チャージ中の音を出す
			if(a % 3 == 1)
			{
				int seID = hMedi->GetMediaObjectID("Data/Media/charge.wav");
				int f = 5000+400*a;
				hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
				hMedi->SetPlayStatus(seID, MOS_FREQUENCY, &f);
				hMedi->PlaySE(seID);
			}
		}
		if(tentacle && a == 0)
		{
			Shot(0);
			tentacle = false;
			t_charge = 0;
		} else if(a > 0){
			t_charge++;
		} else {
			t_charge = 0;
		}
	} else {
		if(a % 6 == 5)
		{
			if(restShot > 0)
			{
				Shot(weaponID);
			} else {
				// 弾切れ音を出す
				int seID = hMedi->GetMediaObjectID("Data/Media/tamagire.wav");
				hMedi->SetPlayStatus(seID, MOS_VOLUME, &e_Config.se_volume);
				hMedi->PlaySE(seID);
			}
		}
		if(b == 1)
		{
			Dead();
		}
	}
}

void CMyShip::Shot(int shotNumber)
{
	switch(shotNumber)
	{
	case 0:		// 触手
		e_taskFactory.CreateShot(0, vecPos, vecPos);
		break;
	case 1:		// 前方ショット
		if(e_taskMgr.shot->GetNumFreeTask() > 1)
		{
			e_taskFactory.CreateShot(1, vecPos, D3DXVECTOR3(0.08f, 0.0f, 0.0f));
			restShot--;
		}
		break;
	case 2:		// 4方向ショット
		if(e_taskMgr.shot->GetNumFreeTask() > 4)
		{
			for(int i=1; i<=4; i++)
			{
				e_taskFactory.CreateShot(1, vecPos, D3DXVECTOR3(0.08f*cos(D3DX_PI/2*i-D3DX_PI/4), 0.08f*sin(D3DX_PI/2*i-D3DX_PI/4), 0.0f));
				restShot--;
			}
		}
		break;
	case 3:		// 前方ミサイル
		if(e_taskMgr.shot->GetNumFreeTask() > 4)
		{
			e_taskFactory.CreateShot(2, vecPos, D3DXVECTOR3(0.08f, 0.0f, 0.0f));
			restShot--;
		}
		break;
	case 4:		// 後方ダブルミサイル
		if(e_taskMgr.shot->GetNumFreeTask() > 4)
		{
			for(int i=-1; i<=1; i+=2)
			{
				e_taskFactory.CreateShot(2, vecPos, D3DXVECTOR3(-0.08f*cos(D3DX_PI/4*i), 0.08f*sin(D3DX_PI/4*i), 0.0f));
				restShot--;
			}
		}
		break;
	case 5:		// フリーウェイショット
		if(e_taskMgr.shot->GetNumFreeTask() > 1)
		{
			e_taskFactory.CreateShot(1, vecPos, D3DXVECTOR3(0.08f*cos(lastMoveRad), -0.08f*sin(lastMoveRad), 0.0f));
			restShot--;
		}
		break;
	case 6:		// 前方3wayショット
		if(e_taskMgr.shot->GetNumFreeTask() > 3)
		{
			for(int i=-1; i<=1; i++)
			{
				e_taskFactory.CreateShot(1, vecPos, D3DXVECTOR3(0.08f*cos(D3DX_PI/6*i), 0.08f*sin(D3DX_PI/6*i), 0.0f));
				restShot--;
			}
		}
		break;
	}
}

void CMyShip::Draw(CHandleGraphics *hGrap)
{
	if(dead)
	{
		return;
	}
	
	if(blink)
	{
		fillMode = 1;
	} else {
		fillMode = 0;
	}
	DrawThing(hGrap);
	if(weaponID != 0)
	{
		objectID = weaponGrapID[weaponID];
		fillMode = 1;
		DrawThing(hGrap);
		fillMode = 0;
		objectID = weaponGrapID[0];
	}
}

bool CMyShip::Revive()
{
	if(dead)
	{
		if(restShip > 0)
		{
			restShip--;
			// 初期位置に移動
			vecPos = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);

			// 死亡を解除
			dead = false;

			// 触手を解除
			t_charge = 0;
			tentacle = false;

			// 無敵時間を設定
			blink = 120;

			return true;
		}
		return false;
	}
	return true;
}

int CMyShip::GetRest()
{
	return restShip;
}

int CMyShip::GetScore()
{
	return score;
}

void CMyShip::AddScore(int pt)
{
	score += pt;
}

void CMyShip::Dead()
{
	if(!dead && !blink)
	{
		if(weaponID != 0)
		{
			e_taskFactory.CreateExplode(1, vecPos);
			e_taskFactory.CreateShot(-1, vecPos, vecPos);
			weaponID = 0;
			t_charge = 0;
			restShot = 0;
			blink = 90;
			return;
		}
		e_taskFactory.CreateExplode(0, vecPos);
		dead = true;
	}
}

void CMyShip::GainWeapon(int wn)
{
	if(!dead && weaponID == 0)
	{
		// 武器取得時のエフェクト
		e_taskFactory.CreateEquipEffect(vecPos);

		// 武器の取得
		weaponID = wn;
		switch(wn)
		{
		case 1:
			restShot = 100;
			break;
		case 2:
			restShot = 120;
			break;
		case 3:
			restShot = 40;
			break;
		case 4:
			restShot = 20;
			break;
		case 5:
			restShot = 100;
			break;
		case 6:
			restShot = 90;
			break;
		}

		// 取得時にも無敵
		blink = 5;
	}
}

CMyShip e_MyShip;
