#ifndef EFFECT_H
#define EFFECT_H

#include "Task.h"
#include "TaskManager.h"

#include "HandleSystem.h"

#include "Thing.h"

//=============================================================
// CEffect
//-------------------------------------------------------------
// 爆発などのエフェクトスプライトのクラス。
//=============================================================
class CEffect : public CThingSprite, CTaskBase
{
public:
	CEffect(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CEffect()
	{
	}
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.effect);
	}
	void operator delete(void *p)
	{
		operator_delete(p, e_taskMgr.effect);
	}

	virtual bool Update() = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
protected:
	bool dead;
};

#endif