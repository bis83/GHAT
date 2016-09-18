#ifndef EQUIPBOMB_H
#define EQUIPBOMB_H

#include "Shot.h"

//=============================================================
// CEquipBomb
//-------------------------------------------------------------
// ‘•”õ”j‰ó‚ÌUŒ‚B
//=============================================================
class CEquipBomb : public CShot
{
public:
	CEquipBomb(CTaskList *taskList, D3DXVECTOR3 vecPos);
	~CEquipBomb();

	bool Update();
	bool Hit(CDynamics *target);
	void Draw(CHandleGraphics *hGrap) {}
	CDynamics *GetDynamics()
	{
		return &hit;
	}
private:
	int timer;
	CBoundingSphere hit;
};

#endif

