#include "TaskManager.h"
#include "SafeRelease.h"

#include "Item.h"
#include "DirBullet.h"
#include "MissileBullet.h"
#include "Tentacle.h"
#include "DirShot.h"
#include "MyShipDeath.h"
#include "Explode.h"
#include "BluePlanet.h"
#include "Seaface.h"
#include "Zako.h"
#include "Asteroid.h"

CTaskManager::CTaskManager()
{
	// 各タスクリストをNULLに
	back = item = shot = enemy = bullet = rig = effect = NULL;
	boss = NULL;
}

void CTaskManager::Init()
{
	UnInit();
	// 各タスクリストを作成
	item = new CTaskList(sizeof(CItem)+1, 62);
	bullet = new CTaskList(sizeof(CMissileBullet)+1, 126);
	shot = new CTaskList(sizeof(CDirShot)+1, 30);
	effect = new CTaskList(sizeof(CExplode)+1, 62);
	back = new CTaskList(sizeof(CSeaface)+1, 14);
	enemy = new CTaskList(sizeof(CZako1)+1, 14);
	rig = new CTaskList(sizeof(CAsteroid)+1, 62);
}

void CTaskManager::UnInit()
{
	// 各タスクリストを安全に解放
	SAFE_DELETE(back);
	SAFE_DELETE(item);
	SAFE_DELETE(shot);
	SAFE_DELETE(enemy);
	SAFE_DELETE(bullet);
	SAFE_DELETE(rig);
	SAFE_DELETE(effect);
	SAFE_DELETE(boss);
}

CTaskManager::~CTaskManager()
{
	UnInit();
}

CTaskManager e_taskMgr;
