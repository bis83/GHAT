#include "SceneMain.h"
#include "SceneGameOver.h"
#include "SceneEnding.h"
#include "SafeRelease.h"

#include "Config.h"
#include "Ranking.h"
#include "MyShip.h"
#include "TaskManager.h"
#include "TaskFactory.h"

#include "Back.h"
#include "MyShip.h"
#include "Item.h"
#include "Bullet.h"
#include "Shot.h"
#include "Effect.h"
#include "Enemy.h"
#include "Rig.h"

CSceneMain::CSceneMain()
{
}

CSceneMain::~CSceneMain()
{
}

void CSceneMain::Init(CSystemScene *_system)
{
	CSceneBase::Init(_system);
	fontID = GetGraphics()->GetDrawObjectID("Data/Texture/font.png");
	pause_f = false;

	itemGetID = GetMedia()->GetMediaObjectID("Data/Media/item.wav");

	// 自機の初期化
	e_MyShip.Init(GetGraphics());

	// タスクマネージャーの初期化
	e_taskMgr.Init();
	e_taskFactory.Init(GetGraphics(), GetMedia());

	GetMedia()->SetPlayStatus(GetMedia()->GetMediaObjectID("Data/Media/airf.wav"), MOS_VOLUME, &e_Config.bgm_volume);
	GetMedia()->PlayBGM(GetMedia()->GetMediaObjectID("Data/Media/airf.wav"));

	wait = 0;
	gameover = false;

	script.Set("Data/Text/Stage1.txt");
}

void CSceneMain::UnInit()
{
}

void CSceneMain::Update()
{
	// ポーズ処理
	if(GetInput(0, e_Config.key_pause) == 1)
	{
		// ポーズ処理の入り切り
		pause_f = pause_f ? false : true;
		if(pause_f)
		{
			// BGMの停止
			GetMedia()->StopBGM();
		} else {
			// BGMの再開
			GetMedia()->RestartBGM();
		}
	}
	// ポーズ中は処理を中断
	if(pause_f)
	{
		return;
	}

	// ステージスクリプトの進行
	if(!script.Update())
	{
		MoveScene(new CSceneEnding());
		return;
	}

	// ゲームオーバー処理
	if(wait > 0)
	{
		wait--;
	} else {
		if(gameover)
		{
			MoveScene(new CSceneGameOver());
			return;
		}
		// 自機が死亡した場合
		if(!e_MyShip.Revive())
		{
			wait = 60;
			gameover = true;
		}
	}

	// 移動と死亡

	// 背景の移動
	for(CTaskIter i(e_taskMgr.back); i.HasNext(); (((CBack*)i.Next())->Update() ? 1 : i.Remove()));
	// アイテムの移動
	for(CTaskIter i(e_taskMgr.item); i.HasNext(); (((CItem*)i.Next())->Update() ? 1 : i.Remove()));
	// 自機の移動
	e_MyShip.Update(GetInput(0, e_Config.key_shot), GetInput(0, e_Config.key_bomb),
		GetInput(0, ANALOG_X), GetInput(0, ANALOG_Y), GetMedia());
	// 敵の移動
	for(CTaskIter i(e_taskMgr.enemy); i.HasNext(); (((CEnemy*)i.Next())->Update(GetMedia()) ? 1 : i.Remove()));
	if(e_taskMgr.boss != NULL)
	{
		if(!e_taskMgr.boss->Update(GetMedia()))
		{
			SAFE_DELETE(e_taskMgr.boss);
			script.BossEnd();
		}
	}
	// ショットの移動
	for(CTaskIter i(e_taskMgr.shot); i.HasNext(); (((CShot*)i.Next())->Update() ? 1 : i.Remove()));
	// 敵弾の移動
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext(); (((CBullet*)i.Next())->Update() ? 1 : i.Remove()));
	// 地形の移動
	for(CTaskIter i(e_taskMgr.rig); i.HasNext(); (((CRig*)i.Next())->Update() ? 1 : i.Remove()));
	
	// エフェクトの移動
	for(CTaskIter i(e_taskMgr.effect); i.HasNext(); (((CEffect*)i.Next())->Update() ? 1 : i.Remove()));

	// 自機の当たり判定
	CTaskBase *t, *k;
	if(!e_MyShip.Blink())
	{
		// 自機と敵
		for(CTaskIter i(e_taskMgr.enemy); i.HasNext();)
		{
			t = i.Next();
			if(((CEnemy*)t)->Hit(&e_MyShip.hitRange))
			{
				((CEnemy*)t)->Damage(1);
				e_MyShip.Dead();
			}
		}
		// 自機とボス
		if(e_taskMgr.boss != NULL)
		{
			if(e_taskMgr.boss->Hit(&e_MyShip.hitRange))
			{
				e_taskMgr.boss->Damage(1);
				e_MyShip.Dead();
			}
		}
		// 自機と敵弾
		for(CTaskIter i(e_taskMgr.bullet); i.HasNext();)
		{
			t = i.Next();
			if(((CBullet*)t)->Hit(&e_MyShip.hitRange))
			{
				((CBullet*)t)->Dead();
				e_MyShip.Dead();
			}
		}
		// 自機と地形
		for(CTaskIter i(e_taskMgr.rig); i.HasNext();)
		{
			t = i.Next();
			if(((CRig*)t)->Hit(&e_MyShip.hitRange))
			{
				((CRig*)t)->Damage(1);
				if(((CRig*)t)->Power() > 0)
				{
					e_MyShip.Dead();
				}
			}
		}
	}
	// 自機とアイテム
	for(CTaskIter i(e_taskMgr.item); i.HasNext();)
	{
		t = i.Next();
		// アイテムを回収する場合
		if(((CItem*)t)->Hit(&e_MyShip.hitRange))
		{
			e_taskFactory.CreateItemGet(((CItem*)t)->vecPos);
			e_MyShip.AddScore(100);
			((CItem*)t)->Dead();
			continue;
		}
		// アイテム回収範囲内に入った場合
		if(((CItem*)t)->Hit(&e_MyShip.itemCollectRange))
		{
			((CItem*)t)->Gather();
			continue;
		}
	}

	// ショットと敵
	for(CTaskIter i(e_taskMgr.shot); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.enemy); j.HasNext();)
		{
			k = j.Next();
			// 接触している場合はショットを殺し敵の体力を減らす
			if(((CShot*)t)->Hit(((CEnemy*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CEnemy*)k)->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				((CEnemy*)k)->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
					// 触手の攻撃で死亡した場合は武器をプレイヤーが取得する
					if(((CEnemy*)k)->IsDead())
					{
						e_MyShip.GainWeapon(((CEnemy*)k)->GetEnemyID());
						// 触手の攻撃の場合は得点アイテムを出現させる
						for(int i=0; i<e_Config.difficult; i++)
						{
							e_taskFactory.CreateItem(((CEnemy*)k)->vecPos,
								D3DXVECTOR3(0.01f*cos((float)timeGetTime()+i*2),
								0.01f*sin((float)timeGetTime()+i*2), 0.0f));
						}
					}

				} else {
					// 撃ち込み点を手に入れる
					e_MyShip.AddScore(20);
				}
			}
		}
		// ショットとボス
		if(e_taskMgr.boss != NULL)
		{
			if(e_taskMgr.boss->Hit(((CShot*)t)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((e_taskMgr.boss->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				e_taskMgr.boss->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
					// 触手の攻撃の場合は得点アイテムを出現させる
					for(int i=0; i<e_Config.difficult; i++)
					{
						e_taskFactory.CreateItem(e_taskMgr.boss->vecPos,
							D3DXVECTOR3(0.01f*cos((float)timeGetTime()+i*2),
							0.01f*sin((float)timeGetTime()+i*2), 0.0f));
					}
				} else {
					// 撃ち込み点を手に入れる
					e_MyShip.AddScore(20);
				}
			}
		}
	}
	// ショットと地形
	for(CTaskIter i(e_taskMgr.shot); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.rig); j.HasNext();)
		{
			k = j.Next();
			// 接触している場合はショットを殺し敵の体力を減らす
			if(((CShot*)t)->Hit(((CRig*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CRig*)k)->vecPos+((CShot*)t)->vecPos)/2);
				((CShot*)t)->Dead();
				((CRig*)k)->Damage(((CShot*)t)->Power());
				if(((CShot*)t)->ShotType() == 0)
				{
				} else {
					// 撃ち込み点を手に入れる
					e_MyShip.AddScore(20);
				}
			}
		}
	}
	// 敵弾と地形
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext();)
	{
		t = i.Next();
		for(CTaskIter j(e_taskMgr.rig); j.HasNext();)
		{
			k = j.Next();
			// 接触している場合はショットを殺し敵の体力を減らす
			if(((CBullet*)t)->Hit(((CRig*)k)->GetDynamics()))
			{
				e_taskFactory.CreateHitEffect((((CRig*)k)->vecPos+((CBullet*)t)->vecPos)/2);
				((CBullet*)t)->Dead();
				((CRig*)k)->Damage(1);
			}
		}
	}
}

void CSceneMain::Draw()
{
	// 背景の描画
	for(CTaskIter i(e_taskMgr.back); i.HasNext(); ((CBack*)i.Next())->Draw(GetGraphics()));
	// アイテムの描画
	for(CTaskIter i(e_taskMgr.item); i.HasNext(); ((CItem*)i.Next())->Draw(GetGraphics()));
	// ショットの描画
	for(CTaskIter i(e_taskMgr.shot); i.HasNext(); ((CBullet*)i.Next())->Draw(GetGraphics()));
	// 敵弾の描画
	for(CTaskIter i(e_taskMgr.bullet); i.HasNext(); ((CBullet*)i.Next())->Draw(GetGraphics()));
	// 自機の描画
	e_MyShip.Draw(GetGraphics());
	// 敵機の描画
	for(CTaskIter i(e_taskMgr.enemy); i.HasNext(); ((CEnemy*)i.Next())->Draw(GetGraphics()));
	if(e_taskMgr.boss != NULL)
	{
		e_taskMgr.boss->Draw(GetGraphics());
	}

	// 地形の描画
	for(CTaskIter i(e_taskMgr.rig); i.HasNext(); ((CRig*)i.Next())->Draw(GetGraphics()));

	// エフェクトの描画
	for(CTaskIter i(e_taskMgr.effect); i.HasNext(); ((CEffect*)i.Next())->Draw(GetGraphics()));

	// ステータス(スコアと残機)の描画
	sprintf(string, "Rest %1d  Score %8d", e_MyShip.GetRest(), e_MyShip.GetScore());
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	D3DXMatrixTranslation(&mat, 360, 0, 0);
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
	GetGraphics()->DrawObject(fontID);
	// 残弾の表示
	if(e_MyShip.Equipping())
	{
		sprintf(string, "Type%1d  Bullet%3d", e_MyShip.GetWeaponID(), e_MyShip.GetBullet());
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 24, 678, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	} else {
		// チャージ率の表示
		sprintf(string, "Charge %3d", e_MyShip.GetCharge());
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 24, 678, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	}

	// FPSの描画
	sprintf(string, "FPS_%2d", GetFPS());
	GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
	GetGraphics()->DrawObject(fontID);

	// ポーズの描画
	if(pause_f)
	{
		sprintf(string, "Pause");
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_STRING, string);
		D3DXMatrixTranslation(&mat, 580, 336, 0);
		GetGraphics()->SetDrawObjectStatus(fontID, DOS_MATRIX, &mat);
		GetGraphics()->DrawObject(fontID);
	}
}
