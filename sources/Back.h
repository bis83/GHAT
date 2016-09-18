#ifndef BACK_H
#define BACK_H

#include "Task.h"
#include "TaskManager.h"

#include "HandleSystem.h"

#include "Thing.h"

//=============================================================
// CBack
//-------------------------------------------------------------
// îwåiÉNÉâÉXÅB
//=============================================================
class CBack : public CTaskBase
{
public:
	CBack(CTaskList *_taskList)
		: CTaskBase(_taskList)
	{
	}
	virtual ~CBack()
	{
	}
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.back);
	}
	void operator delete(void* p)
	{
		operator_delete(p, e_taskMgr.back);
	}

	virtual bool Update() = 0;
	virtual void Draw(CHandleGraphics *hGrap) = 0;
protected:
	bool dead;
};

#endif