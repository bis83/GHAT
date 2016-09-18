#ifndef BULLET_H
#define BULLET_H

#include "Task.h"
#include "TaskManager.h"
#include "HandleSystem.h"

#include "Thing.h"

#include "Dynamics.h"

//=============================================================
// CBullet
//-------------------------------------------------------------
// “G’eƒNƒ‰ƒXB
//=============================================================
class CBullet : public CThingMesh, CTaskBase
{
public:
	CBullet(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CBullet()
	{
	}
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.bullet);
	}
	void operator delete(void* p)
	{
		operator_delete(p, e_taskMgr.bullet);
	}

	virtual bool Update() = 0;
	virtual bool Hit(CDynamics *target) = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;

	void Dead()
	{
		dead = true;
	}
protected:
	// Ž€–S”»’è
	bool dead;

	// ‰æ–ÊŠO”»’è
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
