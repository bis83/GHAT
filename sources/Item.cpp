#include "Item.h"

#include "bgeMath.h"
#include "MyShip.h"

CItem::CItem(CTaskList *_taskList, CHandleGraphics *hGrap, D3DXVECTOR3 vecPos, D3DXVECTOR3 vecVel)
: CThingMesh(), CTaskBase(_taskList)
{
	Set("Data/Mesh/item.x", hGrap);
	vecScale = D3DXVECTOR3(0.12f, 0.12f, 1.0f);
	this->vecPos = vecPos;
	this->vecVel = vecVel;
	billBoarding = true;
	dead = false;
	gather = false;
	hit.c = vecPos;
	hit.r = 0.03f;
}

CItem::~CItem()
{
}

void CItem::Draw(CHandleGraphics *hGrap)
{
	DrawThing(hGrap);
}

bool CItem::Hit(CDynamics *target)
{
	return hit.Hit(target);
}

bool CItem::Update()
{
	if(e_MyShip.Gather())
	{
		gather = true;
		timer = 0;
	}
	// ˆÚ“®
	if(gather)
	{
		// ©‹@•ûŒü‚É•ÏX
		vecVel = MathChangeDirection(vecVel, vecPos, e_MyShip.vecPos);
		if(timer < 30)
		{
			vecVel *= 1.1f;
			timer++;
		}
	}
	vecPos += vecVel;
	hit.c = vecPos;

	if(OutSurface())
	{
		dead = true;
	}

	return !dead;
}

void CItem::Dead()
{
	dead = true;
}

void CItem::Gather()
{
	gather = true;
}
