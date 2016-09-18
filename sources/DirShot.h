#ifndef DIRSHOT_H
#define DIRSHOT_H

#include "Shot.h"

//=============================================================
// CDirShot
//-------------------------------------------------------------
// 指定方向に直進するショット。
//=============================================================
class CDirShot : public CShot
{
public:
	CDirShot(CTaskList *_taskList, CHandleGraphics *hGrap, CHandleMedia *hMedi, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel);
	~CDirShot();

	bool Update();
	void Draw(CHandleGraphics *hGrap);
	bool Hit(CDynamics *target);
	CDynamics *GetDynamics()
	{
		return &hit;
	}
private:
	D3DXVECTOR3 vecVel;
	CBoundingSphere hit;
};

#endif
