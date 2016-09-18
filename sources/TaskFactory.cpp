#include "TaskFactory.h"

#include "Item.h"
#include "DirBullet.h"
#include "MissileBullet.h"
#include "EquipBomb.h"
#include "Tentacle.h"
#include "DirShot.h"
#include "MissileShot.h"
#include "MyShipDeath.h"
#include "Explode.h"
#include "BackStar.h"
#include "BackAsteroid.h"
#include "BluePlanet.h"
#include "Reentry.h"
#include "Sky.h"
#include "Cloud.h"
#include "Seaface.h"
#include "Zako.h"
#include "Smoke.h"
#include "Equip.h"
#include "HitBullet.h"
#include "ItemGet.h"
#include "Boss.h"
#include "Asteroid.h"
#include "Block.h"
#include "FortBack.h"
#include "Galaxy.h"

void CTaskFactory::Init(CHandleGraphics *_hGrap, CHandleMedia *_hMedi)
{
	hGrap = _hGrap;
	hMedi = _hMedi;
}

void CTaskFactory::CreateItem(D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
{
	new CItem(e_taskMgr.item, hGrap, vecPos, vecVel);
}

void CTaskFactory::CreateBullet(int bulletType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
{
	switch(bulletType)
	{
	case 1:
		new CDirBullet(e_taskMgr.bullet, hGrap, vecPos, vecVel);
		break;
	case 2:
		new CMissileBullet(e_taskMgr.bullet, hGrap, vecPos, vecVel);
		break;
	}
}

void CTaskFactory::CreateEnemy(int enemyType, int enemyPattern, D3DXVECTOR3 vecPos)
{
	switch(enemyType)
	{
	case 1:
		new CZako1(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	case 2:
		new CZako2(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	case 3:
		new CZako3(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	case 4:
		new CZako4(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	case 5:
		new CZako5(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	case 6:
		new CZako6(e_taskMgr.enemy, hGrap, hMedi, vecPos, enemyPattern);
		break;
	}
}

void CTaskFactory::CreateBoss(int bossType)
{
	switch(bossType)
	{
	case 1:
		if(e_taskMgr.boss == NULL)
		{
			e_taskMgr.boss = new CBoss1(hGrap, hMedi);
		}
		break;
	case 2:
		if(e_taskMgr.boss == NULL)
		{
			e_taskMgr.boss = new CBoss2(hGrap, hMedi);
		}
		break;
	case 3:
		if(e_taskMgr.boss == NULL)
		{
			e_taskMgr.boss = new CBoss3(hGrap, hMedi);
		}
		break;
	}
}

void CTaskFactory::CreateShot(int shotType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
{
	switch(shotType)
	{
	case -1:	// •Ší”š”­
		new CEquipBomb(e_taskMgr.shot, vecPos);
		break;
	case 0:		// GŽè
		new CTentacle(e_taskMgr.shot, hGrap, hMedi, e_MyShip.vecPos);
		break;
	case 1:		// •ûŒü’e
		new CDirShot(e_taskMgr.shot, hGrap, hMedi, vecPos, vecVel);
		break;
	case 2:		// ƒ~ƒTƒCƒ‹’e
		new CMissileShot(e_taskMgr.shot, hGrap, hMedi, vecPos, vecVel);
		break;
	}
}

void CTaskFactory::CreateExplode(int explodeType, D3DXVECTOR3 vecPos)
{
	switch(explodeType)
	{
	case 0:
		new CMyShipDeath(e_taskMgr.effect, hGrap, hMedi, vecPos);
		break;
	default:
		new CExplode(e_taskMgr.effect, hGrap, hMedi, vecPos, explodeType);
		break;
	}
}

void CTaskFactory::CreateMissileSmoke(D3DXVECTOR3 vecPos)
{
	new CSmoke(e_taskMgr.effect, hGrap, vecPos);
}

void CTaskFactory::CreateBack(int backType)
{
	switch(backType)
	{
	case 1:
		new CBackStar(e_taskMgr.back, hGrap);
		break;
	case 2:
		new CBluePlanet(e_taskMgr.back, hGrap);
		break;
	case 3:
		new CReentry(e_taskMgr.back, hGrap);
		break;
	case 4:
		new CSky(e_taskMgr.back, hGrap);
		break;
	case 5:
		new CCloud(e_taskMgr.back, hGrap, 1);
		break;
	case 6:
		new CSeaface(e_taskMgr.back, hGrap);
		break;
	case 7:
		new CCloud(e_taskMgr.back, hGrap, 2);
		break;
	case 8:
		new CBackAsteroid(e_taskMgr.back, hGrap);
		break;
	case 9:
		new CFortBack(e_taskMgr.back, hGrap);
		break;
	case 10:
		new CGalaxy(e_taskMgr.back, hGrap);
		break;
	}
}

void CTaskFactory::CreateRig(int rigType, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
{
	switch(rigType)
	{
	case 1:
		new CAsteroid(e_taskMgr.rig, hGrap, vecPos, vecVel);
		break;
	case 2:
		new CBlock(e_taskMgr.rig, hGrap, vecPos, vecVel, ((e_taskMgr.rig->GetNumActiveTask() % 4) ? 1 : 2));
		break;
	}
}

void CTaskFactory::CreateEquipEffect(D3DXVECTOR3 vecPos)
{
	new CEquip(e_taskMgr.effect, hGrap, hMedi, vecPos);
}

void CTaskFactory::CreateHitEffect(D3DXVECTOR3 vecPos)
{
	new CHitBullet(e_taskMgr.effect, hGrap, hMedi, vecPos);
}

void CTaskFactory::CreateItemGet(D3DXVECTOR3 vecPos)
{
	new CItemGet(e_taskMgr.effect, hGrap, hMedi, vecPos);
}

CTaskFactory e_taskFactory;
