#ifndef SHOT_H
#define SHOT_H

#include "HandleSystem.h"
#include "Dynamics.h"

#include "Task.h"
#include "TaskManager.h"

#include "Thing.h"

//=============================================================
// CShot
//-------------------------------------------------------------
// 自機のショットのクラス。
//=============================================================
class CShot : public CThingMesh, CTaskBase
{
public:
	CShot(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CShot()
	{
	}
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.shot);
	}
	void operator delete(void* p)
	{
		operator_delete(p, e_taskMgr.shot);
	}
	virtual bool Update() = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
	virtual CDynamics *GetDynamics() = 0;

	void Dead()
	{
		dead = true;
	}

	int Power()
	{
		return power;
	}

	int ShotType()
	{
		return shotType;
	}
protected:
	// 死亡判定
	bool dead;
	// 威力
	int power;
	int shotType;

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
