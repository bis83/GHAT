#ifndef RIG_H
#define RIG_H

#include "Task.h"
#include "TaskManager.h"

#include "HandleSystem.h"
#include "Dynamics.h"

#include "Thing.h"

//=============================================================
// CRig
//-------------------------------------------------------------
// 地形クラス。味方と敵両方への当たり判定を取る。
//=============================================================
class CRig : public CThingMesh, CTaskBase
{
public:
	CRig(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CRig()
	{
	}
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.rig);
	}
	void operator delete(void *p)
	{
		operator_delete(p, e_taskMgr.rig);
	}

	virtual bool Update() = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
	virtual CDynamics* GetDynamics() = 0;
	void Damage(int d)
	{
		life -= d;
	}
	int Power()
	{
		return power;
	}
protected:
	bool dead;
	int life;
	int power;

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