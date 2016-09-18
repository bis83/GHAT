#include "Block.h"

#include "TaskFactory.h"

CBlock::CBlock(CTaskList *taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel, int type)
: CRig(taskList)
{
	switch(type)
	{
	case 1:
		life = 10000;
		Set("Data/Mesh/block.x", hGrap);
		break;
	case 2:
		life = 10;
		Set("Data/Mesh/block2.x", hGrap);
		break;
	}
	vecScale = D3DXVECTOR3(0.15f, 0.15f, 0.15f);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	hit.c = vecPos;
	hit.r = 0.07f;

	dead = false;
	power = 1;
}

CBlock::~CBlock()
{
}

bool CBlock::Update()
{
	vecPos += vecVel;
	hit.c = vecPos;
	if(life <= 0)
	{
		e_taskFactory.CreateExplode(1, vecPos);
		dead = true;
	}
	if(OutSurface())
	{
		dead = true;
	}
	return !dead;
}

void CBlock::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}

bool CBlock::Hit(CDynamics *target)
{
	return hit.Hit(target);
}