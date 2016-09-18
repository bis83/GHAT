#ifndef TASKFACTORY_H
#define TASKFACTORY_H

#include "TaskManager.h"

#include "HandleSystem.h"

//=============================================================
// CTaskFactory
//-------------------------------------------------------------
// 各種タスクを生成する工場クラス。
//=============================================================
class CTaskFactory
{
public:
	CTaskFactory()
	{
	}
	~CTaskFactory()
	{
	}
	void Init(CHandleGraphics *_hGrap, CHandleMedia *_hMedi);

	// アイテムの作成
	void CreateItem(D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// 自弾の作成
	void CreateShot(int shotType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// 敵の作成
	void CreateEnemy(int enemyType, int enemyPattern, D3DXVECTOR3 vecPos);

	// ボスの作成
	void CreateBoss(int bossType);

	// 弾の作成
	void CreateBullet(int bulletType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);

	// 爆発の作成
	void CreateExplode(int explodeType, D3DXVECTOR3 vecPos);

	// アイテム取得時のエフェクトの作成
	void CreateItemGet(D3DXVECTOR3 vecPos);

	// 装備時のエフェクト作成
	void CreateEquipEffect(D3DXVECTOR3 vecPos);

	// 被弾時のエフェクト作成
	void CreateHitEffect(D3DXVECTOR3 vecPos);

	// ミサイルの煙の作成
	void CreateMissileSmoke(D3DXVECTOR3 vecPos);

	// 背景の作成
	void CreateBack(int backType);

	// 地形の作成
	void CreateRig(int rigType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
private:
	// グラフィックスへのハンドル
	CHandleGraphics *hGrap;
	// メディアへのハンドル
	CHandleMedia *hMedi;
};

extern CTaskFactory e_taskFactory;

#endif
