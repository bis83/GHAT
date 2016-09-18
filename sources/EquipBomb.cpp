#include "EquipBomb.h"

CEquipBomb::CEquipBomb(CTaskList *taskList, D3DXVECTOR3 vecPos)
: CShot(taskList)
{
	shotType = -1;
	power = 4;
	this->vecPos = vecPos;
	hit.c = vecPos;
	hit.r = 0.15f;

	timer = 0;
}

CEquipBomb::~CEquipBomb()
{
}

bool CEquipBomb::Update()
{
	timer++;
	return timer < 15;
}

bool CEquipBomb::Hit(CDynamics *target)
{
	return hit.Hit(target);
}