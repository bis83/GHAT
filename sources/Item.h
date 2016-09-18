#ifndef ITEM_H
#define ITEM_H

#include "Task.h"
#include "Thing.h"
#include "TaskManager.h"
#include "HandleSystem.h"

#include "Dynamics.h"

//=============================================================
// CItem
//-------------------------------------------------------------
// アイテムクラス。
// 今回は得点アイテムのみなので、これ以外はない。
//=============================================================
class CItem : public CTaskBase, public CThingMesh
{
public:
	CItem(CTaskList *_taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CItem();
	void* operator new(size_t t)
	{
		return operator_new(t, e_taskMgr.item);
	}
	void operator delete(void *p)
	{
		operator_delete(p, e_taskMgr.item);
	}

	bool Update();
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap);

	void Dead();
	void Gather();

	D3DXVECTOR3 vecVel;
private:
	bool gather;
	bool dead;
	int timer;
	CBoundingSphere hit;

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