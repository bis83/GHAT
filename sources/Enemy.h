#ifndef ENEMY_H
#define ENEMY_H

#include "Task.h"
#include "Thing.h"

#include "Dynamics.h"
#include "HandleSystem.h"

#include "TaskManager.h"
#include "MyShip.h"

//=============================================================
// CEnemy
//-------------------------------------------------------------
// 敵タスクの基底クラス。
//=============================================================
class CEnemy : public CThingMesh, public CTaskBase
{
public:
	CEnemy(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CEnemy()
	{
	}
	// new, deleteのオーバーライド
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.enemy);
	}
	void operator delete(void* p)
	{
		operator_delete(p, e_taskMgr.enemy);
	}

	// 更新、当たり判定、描画
	virtual bool Update(CHandleMedia *hMedi) = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;

	void Dead()
	{
		dead = true;
	}
	void Damage(int d)
	{
		life -= d;
	}
	int GetEnemyID()
	{
		return enemyID;
	}
	bool IsDead()
	{
		return dead || life <= 0;
	}
	// ダイナミクスの取得
	virtual CDynamics* GetDynamics() = 0;
protected:
	// エネミー番号
	int enemyID;
	// 耐久力
	int life;
	// 死亡フラグ
	bool dead;

	// 画面外判定
	bool OutSurface()
	{
		if(vecPos.x > 3.0f || vecPos.x < -3.0f || vecPos.y > 3.0f || vecPos.y < -3.0f)
		{
			return true;
		}
		return false;
	}
};

#endif